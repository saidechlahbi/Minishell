/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:54:31 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/27 20:17:52 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	open_specific_file(t_redirection *redirec)
{
	if (redirec->is_ambg)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirec->file, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirec->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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
