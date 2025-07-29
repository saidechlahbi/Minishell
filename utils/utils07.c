/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils07.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:41:22 by schahir           #+#    #+#             */
/*   Updated: 2025/07/29 17:33:24 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_error(char *s)
{
	return (!ft_strcmp(s, ">") || !ft_strcmp(s, "<") || !ft_strcmp(s, ">>")
		|| !ft_strcmp(s, "<<"));
}

int	is_op(char *s)
{
	return (!ft_strcmp(s, "|") || !ft_strcmp(s, ">") || !ft_strcmp(s, "<")
		|| !ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"));
}

int	is_pipe(char *s)
{
	return (!ft_strcmp(s, "|"));
}

int	check_literal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				i++;
			else if (is_expandable(str[i]))
			{
				while (str[i] && is_expandable2(str[i]))
					i++;
			}
		}
		else
			return (1);
	}
	return (0);
}

int	check_last(char *last)
{
	return (last && (last[1] == '?' || is_expandable(last[1])));
}
