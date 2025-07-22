/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:54:31 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/22 15:52:57 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int open_files(t_cmds *command)
{
    t_redirection *redirec;

    redirec = command->redirection;
    while (redirec)
    {
        if (redirec->type == IN_FILE)
        {
            if (redirec->is_ambigious)
                return (printf("bash: ambiguous redirect\n"), 0);
            redirec->fd = open(redirec->file, O_RDONLY, 0644);
            if (redirec->fd == -1)
                return (printf("minishell: %s: No such file or directory\n", redirec->file), 0);
        }
        else if (redirec->type == OUT_FILE)
        {
            if (redirec->is_ambigious)
                return (printf("bash: ambiguous redirect\n"), 0);
            redirec->fd = open(redirec->file, O_WRONLY | O_CREAT, 0644);
            if (redirec->fd == -1)
                return (printf("minishell: %s: No such file or directory\n", redirec->file), 0);
        }
        else if (redirec->type == APP_FILE)
        {
            if (redirec->is_ambigious)
                return (printf("bash: ambiguous redirect\n"), 0);
            redirec->fd = open(redirec->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (redirec->fd == -1)
                return (printf("minishell: %s: No such file or directory\n", redirec->file), 0);
        }
        redirec = redirec->next;
    }
    return 1;
}

void redirection(t_cmds *command)
{
    t_redirection *tmp;

    command->read_from = 0;
    command->write_in = 0;
    tmp = command->redirection;
    while (tmp)
    {
        if (tmp->type == IN_FILE || tmp->type == HERE_DOC)
            command->read_from = tmp->fd;
        else if (tmp->type == OUT_FILE || tmp->type == APP_FILE)
            command->write_in = tmp->fd;
        tmp = tmp->next;
    }
    return;
}

static int is_fd_open_fstat(int fd) {
    struct stat st;
    return fstat(fd, &st) == 0;
}

void close_all_fds_fstat(int start)
{
    int count;

    count = 0;
    while (start < 1024)
    {
        if (is_fd_open_fstat(start))
            close(start);
        else
            count++;
        if (count == 20)
            break;
        start ++;
    }
}
