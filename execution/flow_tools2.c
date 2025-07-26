/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:14:17 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/25 23:33:10 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args_of_cmd(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD || token->type == BUILTIN || token->type == ARG)
			count++;
		token = token->next;
	}
	return (count);
}

char	**fill_cmd(t_token *token, t_garbage **garbage)
{
	char	**cmd;
	int		count;

	cmd = NULL;
	if (count_args_of_cmd(token) == 0)
		return (NULL);
	cmd = ft_malloc(sizeof(char *), (count_args_of_cmd(token) + 1), garbage);
	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD || token->type == BUILTIN)
		{
			cmd[count] = ft_strdup(token->value, garbage);
			count++;
		}
		if (token->type == ARG)
		{
			cmd[count] = ft_strdup(token->value, garbage);
			count++;
		}
		token = token->next;
	}
	cmd[count] = NULL;
	return (cmd);
}
