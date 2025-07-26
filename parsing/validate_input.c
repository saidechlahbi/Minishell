/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:55:51 by schahir           #+#    #+#             */
/*   Updated: 2025/07/26 20:22:13 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_input(t_token *token)
{
	t_token	*cur;

	if (!token || !ft_strcmp(token->value, "|"))
	{
		ft_putstr_fd("Error : Syntax\n", 2);
		set_status(2);
		return (1);
	}
	cur = token;
	while (cur)
	{
		if ((is_error(cur->value) && cur->next && is_op(cur->next->value))
			|| (is_op(cur->value) && !cur->next) || (is_pipe(cur->value)
				&& cur->next && is_pipe(cur->next->value)))
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			set_status(2);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

void	delimiter(t_token *token)
{
	int	i;

	while (token)
	{
		if (token->type == DELIMITER)
		{
			i = 0;
			while (token->value[i])
			{
				if (token->value[i] == '\'' || token->value[i] == '"')
					token->inq = 1;
				i++;
			}
		}
		token = token->next;
	}
}
