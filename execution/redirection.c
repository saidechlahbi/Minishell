/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:54:31 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/16 14:27:08 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int open_files(t_cmds *command)
{
    t_redirection *redirec;

    redirec = commands->redirection;
    while (redirec)
    {
        if (redirec->type == IN_FILE)
        {
            redirec->fd = open(redirec->file, O_RDONLY, 0644);
            if (redirec->fd == -1)
                return (printf("minishell: %s: No such file or directory\n", redirect->file), 0);
        }
        else if (redirec->type == OUT_FILE)
        {
            redirec->fd = open(redirec->file, O_WRONLY | O_CREAT, 0644);
            if (redirec->fd == -1)
                return (printf("minishell: %s: No such file or directory\n", redirect->file), 0);
        }
        else if (redirec->type == APP_FILE)
        {
            redirec->fd = open(redirec->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (redirec->fd == -1)
                return (printf("minishell: %s: No such file or directory\n", redirect->file), 0);
        }
        redirec = redirec->next;
    }
}

void redirection(t_cmds *commands)
{
    t_redirection *tmp;

    open_files(commands);
    while (commands)
    {
        commands->read_from = 0;
        commands->write_in = 0;
        tmp = commands->redirection;
        while (tmp)
        {
            if (tmp->type == IN_FILE)
                commands->read_from = tmp->fd;
            else if (tmp->type == OUT_FILE || tmp->type == APP_FILE)
                commands->write_in = tmp->fd;
            tmp = tmp->next;
        }
        commands = commands->next;
    }
    return;
}

static int is_fd_open_fstat(int fd) {
    struct stat st;
    return fstat(fd, &st) == 0;
}

void close_all_fds_fstat(int start)
{
    while (start <= 1024)
    {
        if (is_fd_open_fstat(fd))
            close(fd);
        start ++;
    }
}
