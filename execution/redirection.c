/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:54:31 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/07 13:58:23 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void open_herdoc(t_redirection *redirec, int *pid)
{
    char *line;
    int fd;
    
    redirec->fd = open(redirec->file, O_CREAT | O_WRONLY, 0644);
    unlink(redirec->file);
    *pid = fork();
    if (*pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        line = readline(">");
        while (line && ft_strcmp(line, redirec->delimiter))
        {
            write(redirec->fd, line, ft_strlen(line));
            free(line);
            line = readline(">");
        }
        free(line);
        fd = open(redirec->file, O_CREAT | O_WRONLY, 0644);
        close(redirec->fd);
        unlink(redirec->file);
        redirec->fd = fd;
        exit(0);
    }
}

 void open_files(t_cmds *commands)
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
            if (redirec->type == IN_FILE)
                redirec->fd = open(redirec->file, O_RDONLY, 0644);
            else if (redirec->type == OUT_FILE)
                redirec->fd = open(redirec->file, O_WRONLY | O_CREAT, 0644);
            else if (redirec->type == APP_FILE)
                redirec->fd = open(redirec->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            else if (redirec->type == HERE_DOC)
            {
                open_herdoc(redirec, &pid);
                waitpid(pid, &status, 0);
                if (WIFEXITED(status) != 0)
                    break;
            }
            redirec = redirec->next;
        }
        commands = commands->next;
    }
}
