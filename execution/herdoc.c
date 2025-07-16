/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 04:44:31 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/16 14:28:00 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void read_from_stdin(t_redirection *redirec)
{
    char *line;

    line = readline("> ");
    if (!line)
        exit(1);
    while (line && ft_strcmp(line, redirec->delimiter))
    {
        write(redirec->fd, line, ft_strlen(line));
        free(line);
        line = readline("> ");
        if (!line)
            exit(1);
    }
    free(line);
}

static void open_herdoc(t_redirection *redirec, int *pid, t_garbage *garbage)
{    
    *pid = fork();
    redirec->fd = open(redirec->file, O_CREAT | O_WRONLY, 0644);
    if (redirec->fd == -1)
        perror(redirec->file);
    unlink(redirec->file);
    if (*pid == -1)
    {
        perror("fork");
        get_out_from_here(garbage, 1);
    }
    if (*pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        read_from_stdin(redirec);
        close_all_fds_fstat(0);
        get_out_from_here(garbage, 0);
    }
    redirec->fd = open(redirec->file, O_CREAT | O_WRONLY, 0644);
    if (redirec->fd == -1)
        perror(redirec->file);
    unlink(redirec->file);
}

void herdoc(t_cmds *commands, int *exit_status)
{
    t_redirection *redirec;
    int pid;
    int status;

    if (!commands->redirection)
        return;
    pid = 0;
    while (commands)
    {
        redirec = commands->redirection;
        while (redirec)
        {
            else if (redirec->type == HERE_DOC)
            {
                open_herdoc(redirec, &pid);
                waitpid(pid, &status, 0);
                if (!WIFEXITED(status))
                {
                    if (WIFSIGNALED(status))
                        *exit_status = WTERMSIG(status) + 128;
                    return ;
                }
                else
                    *exit_status = 0;
            }
            redirec = redirec->next;
        }
        commands = commands->next;
    }
}
