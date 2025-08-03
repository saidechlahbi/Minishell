/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:14:46 by schahir           #+#    #+#             */
/*   Updated: 2025/08/03 16:03:19 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	process_redirection(t_token *token)
{
	if (token->type == RED_OUT)
		token->next->type = OUT_FILE;
	else if (token->type == RED_IN)
		token->next->type = IN_FILE;
	else if (token->type == APPEND)
		token->next->type = APP_FILE;
	else if (token->type == HERE_DOC)
		token->next->type = DELIMITER;
}

static void	specify_word(t_token *token, t_token *prev)
{
	if (prev->type == CMD || prev->type == BUILTIN)
	{
		if (prev->next && !ft_strcmp(prev->value, "export"))
			token->exp = EXPORT;
		token->type = ARG;
	}
	else
	{
		if (is_builtin(token->value))
			token->type = BUILTIN;
		else
			token->type = CMD;
	}
}

void	lexing(t_token *token)
{
	t_token	*prev;

	prev = token;
	if (token && (token->type == WORD || token->type == ARG))
	{
		if (is_builtin(token->value))
		{
			if (token->next && !ft_strcmp(token->value, "export"))
				token->next->exp = EXPORT;
			token->type = BUILTIN;
		}
		else
			token->type = CMD;
		token = token->next;
	}
	while (token)
	{
		if (token->type == RED_OUT || token->type == RED_IN
			|| token->type == APPEND || token->type == HERE_DOC)
			process_redirection(token);
		else if (token->type == WORD)
			specify_word(token, prev);
		if (token->type == CMD || token->type == BUILTIN || token->type == PIPE)
			prev = token;
		token = token->next;
	}
}
