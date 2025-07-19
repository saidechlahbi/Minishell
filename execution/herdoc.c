/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 04:44:31 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/19 01:56:34 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void reset_terminal(void)
// {
//     struct termios term;
//     tcgetattr(STDIN_FILENO, &term);
//     term.c_lflag |= (ECHO | ICANON);
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

static void read_from_stdin(t_redirection *redirec, int fd)
{
    char *line;
    while (1)
    {
        // reset_terminal();
        line = readline("> ");
        if (!line)
        {
            ft_putstr_fd("Minishell: warning: here-document at line 4", 2);
            ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(redirec->file, 2);
            ft_putstr_fd("')\n",2);
            break;
        }
        if (ft_strcmp(line, redirec->delimiter) == 0) {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
        // reset_terminal();
    }
    return ;
}

static void open_herdoc(t_redirection *redirec, int *pid, t_garbage *garbage)
{    
    int fd;
    
    fd = open(redirec->file, O_CREAT | O_WRONLY, 0644);
    redirec->fd = open(redirec->file, O_RDONLY);
    if (redirec->fd == -1 || fd == -1)
        perror(redirec->file);
    unlink(redirec->file);
    *pid = fork();
    if (*pid == -1)
    {
        perror("fork");
        get_out_from_here(garbage, 1);
    }
    if (*pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        read_from_stdin(redirec, fd);
        // close_all_fds_fstat(3);
        // get_out_from_here(garbage, 0);
        exit(1);
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
            *status = 0;
            open_herdoc(redirec, &pid, garbage);
            waitpid(pid, status, 0);
            if (WIFSIGNALED(*status))
            {
                *exit_status = WTERMSIG(*status) + 128;
                return 0;
            }
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
    if (WIFEXITED(status))
    {
        *exit_status = WEXITSTATUS(status);
        return 1;
    }
    return 1;
}
