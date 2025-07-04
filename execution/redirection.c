/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:54:31 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/04 12:02:52 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void open_her_doc(t_redirection *redirec)
{
    char *line;
    int fd;

    redirec->fd = open(redirec->file, O_CREAT | O_WRONLY, 0644);
    unlink(redirec->file);
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
}

 void open_files(t_cmds *commands)
{
    t_redirection *redirec;

    if (!commands->redirection)
        return;
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
                open_her_doc(redirec);
            redirec = redirec->next;
        }
        commands = commands->next;
    }
}
