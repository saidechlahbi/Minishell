/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:54:31 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/10 01:18:24 by sechlahb         ###   ########.fr       */
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

static void open_herdoc(t_redirection *redirec, int *pid)
{    
    redirec->fd = open(redirec->file, O_CREAT | O_WRONLY, 0644);
    if (redirec->fd == -1)
        perror(redirec->file);
    unlink(redirec->file);
    *pid = fork();
    if (*pid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (*pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        read_from_stdin(redirec);
        exit(0);
    }
    close(redirec->fd);
    redirec->fd = open(redirec->file, O_CREAT | O_WRONLY, 0644);
    if (redirec->fd == -1)
        perror(redirec->file);
    unlink(redirec->file);
}

static void open_files(t_cmds *commands)
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
            {
                redirec->fd = open(redirec->file, O_RDONLY, 0644);
                if (redirec->fd == -1)
                    break;
            }
            else if (redirec->type == OUT_FILE)
            {
                redirec->fd = open(redirec->file, O_WRONLY | O_CREAT, 0644);
                if (redirec->fd == -1)
                    break;
            }
            else if (redirec->type == APP_FILE)
            {
                redirec->fd = open(redirec->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (redirec->fd == -1)
                    break;
            }
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
