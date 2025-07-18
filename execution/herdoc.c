/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 04:44:31 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/18 03:22:10 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void read_from_stdin(t_redirection *redirec)
{
    char *line;
    
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            write(STDERR_FILENO, "\n", 1);
            break;
        }
        if (ft_strcmp(line, redirec->delimiter) == 0) {
            free(line);
            break;
        }
        write(redirec->fd, line, ft_strlen(line));
        write(redirec->fd, "\n", 1);
        free(line);
    }
    return ;
}

static void open_herdoc(t_redirection *redirec, int *pid, t_garbage *garbage)
{    
    *pid = fork();

    if (*pid == -1)
    {
        perror("fork");
        get_out_from_here(garbage, 1);
    }
    if (*pid == 0)
    {
        redirec->fd = open(redirec->file, O_CREAT | O_WRONLY, 0644);
        if (redirec->fd == -1)
            perror(redirec->file);
        unlink(redirec->file);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        read_from_stdin(redirec);
        close_all_fds_fstat(0);
        get_out_from_here(garbage, 0);
    }
    else
        g_global_signal = -1;
}

static int list_resdirect(t_redirection *redirec, int *exit_status, int *status, t_garbage *garbage)
{
   int pid;
   
    while (redirec)
    {
        if (redirec->type == HERE_DOC)
        {
            open_herdoc(redirec, &pid, garbage);
            waitpid(pid, status, 0);
            if (WIFSIGNALED(*status))
            {
                *exit_status = WTERMSIG(*status) + 128;
                return 0;
            }
            redirec->fd = open(redirec->file, O_CREAT | O_RDWR, 0644);
            if (redirec->fd == -1)
                perror(redirec->file);
            unlink(redirec->file);
        }
        redirec = redirec->next;
    }
    return 1;
}

int herdoc(t_cmds *commands, int *exit_status, t_garbage *garbage)
{
    t_redirection *redirec;
    int status;

    status = 0;
    while (commands)
    {
        redirec = commands->redirection;
        if (list_resdirect(redirec, exit_status, &status, garbage))
            commands = commands->next;
        else
            return 0;
    }
    if (WIFSIGNALED(status))
    {
        *exit_status = WTERMSIG(status) + 128;
        return 0;
    }
    if (WIFEXITED(status))
    {
        *exit_status = WEXITSTATUS(status);
        return 1;
    }
    return 1;
}
