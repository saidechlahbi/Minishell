/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:33:00 by schahir           #+#    #+#             */
/*   Updated: 2025/07/26 20:20:52 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *s)
{
	return (!ft_strcmp(s, "echo") || !ft_strcmp(s, "export") || !ft_strcmp(s,
			"unset") || !ft_strcmp(s, "exit") || !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "env") || !ft_strcmp(s, "cd"));
}

int	is_operator(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (RED_OUT);
	else if (c == '<')
		return (RED_IN);
	return (-1);
}

int	is_append(char *s)
{
	if (!ft_strcmp(s, ">>"))
		return (APPEND);
	else if (!ft_strcmp(s, "<<"))
		return (HERE_DOC);
	return (-1);
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
