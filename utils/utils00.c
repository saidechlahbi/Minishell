/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:33:00 by schahir           #+#    #+#             */
/*   Updated: 2025/07/13 14:45:03 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *s)
{
	return (!ft_strncmp(s, "echo", 4) || !ft_strncmp(s, "export", 6)
		|| !ft_strncmp(s, "unset", 5) || !ft_strncmp(s, "exit", 4)
		|| !ft_strncmp(s, "pwd", 3) || !ft_strncmp(s, "env", 3)
		|| !ft_strncmp(s, "cd", 2));
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
	if(!ft_strncmp(s, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(s, "<<", 2))
		return (HERE_DOC);
	return (-1);
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int is_op(char *s)
{
	return (!ft_strncmp(s, "|", 1) || !ft_strncmp(s, ">", 1) 
	|| !ft_strncmp(s, "<", 1) || !ft_strncmp(s, ">>", 2) 
	|| !ft_strncmp(s, "<<", 2));
}

int is_error(char *s)
{
	return (!ft_strncmp(s, ">", 1) || !ft_strncmp(s, "<", 1)
	|| !ft_strncmp(s, ">>", 2) || !ft_strncmp(s, "<<", 2));
}
