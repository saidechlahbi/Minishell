/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:54:31 by sechlahb          #+#    #+#             */
/*   Updated: 2025/08/05 15:10:31 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	open_specific_file(t_redirection *redirec)
{
	char		*msg;
	t_garbage	*garbage;

	garbage = f(NULL);
	if (redirec->is_ambg)
	{
		msg = ft_strjoin("minishell: ", redirec->file, &garbage);
		msg = ft_strjoin(msg, ": ambiguous redirect\n", &garbage);
		ft_putstr_fd(msg, 2);
		return (FALSE);
	}
	if (redirec->type == IN_FILE)
		redirec->fd = open(redirec->file, O_RDONLY, 0644);
	if (redirec->type == OUT_FILE)
		redirec->fd = open(redirec->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirec->type == APP_FILE)
		redirec->fd = open(redirec->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redirec->fd == -1)
	{
		msg = ft_strjoin("minishell: ", redirec->file, &garbage);
		msg = ft_strjoin(msg, ": No such file or directory\n", &garbage);
		ft_putstr_fd(msg, 2);
		return (FALSE);
	}
	return (TRUE);
}

int	open_files(t_cmds *command)
{
	t_redirection	*redirec;

	redirec = command->redirection;
	while (redirec)
	{
		if (open_specific_file(redirec) == FALSE)
			return (FALSE);
		redirec = redirec->next;
	}
	return (TRUE);
}

int	redirection(t_cmds *command)
{
	t_redirection	*tmp;

	if (open_files(command) == FALSE)
		return (FALSE);
	tmp = command->redirection;
	while (tmp)
	{
		if (tmp->type == IN_FILE || tmp->type == HERE_DOC)
			command->read_from = tmp->fd;
		else if (tmp->type == OUT_FILE || tmp->type == APP_FILE)
			command->write_in = tmp->fd;
		tmp = tmp->next;
	}
	return (TRUE);
}
