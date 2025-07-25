/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:14:46 by schahir           #+#    #+#             */
/*   Updated: 2025/07/24 21:32:48 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
void	lexing(t_token *token)
{
	t_token	*prev;
	int		i;

	prev = token;
	i = 0;
	if (token && token->type == WORD)
	{
		if (is_builtin(token->value))
			token->type = BUILTIN;
		else
			token->type = CMD;
		prev = token;
		token = token->next;
	}
	while (token)
	{
		if (token->type == RED_OUT)
		{
			token->next->type = OUT_FILE;
			while (token->next->value[i])
			{
				if (token->next->value[i] == '$')
					token->next->expanded = EXPANDED;
				i++;
			}
			i = 0;
		}
		if (token->type == APPEND)
		{
			token->next->type = APP_FILE;
			while (token->next->value[i])
			{
				if (token->next->value[i] == '$')
					token->next->expanded = EXPANDED;
				i++;
			}
			i = 0;
		}
		else if (token->type == RED_IN)
		{
			token->next->type = IN_FILE;
			while (token->next->value[i])
			{
				if (token->next->value[i] == '$')
					token->next->expanded = EXPANDED;
				i++;
			}
			i = 0;
		}
		else if (token->type == HERE_DOC)
			token->next->type = DELIMITER;
		if (token->type == WORD)
		{
			if (prev->type == CMD || prev->type == BUILTIN)
				token->type = ARG;
			else
				token->type = CMD;
		}
		if (token->type == CMD || token->type == BUILTIN || token->type == PIPE)
			prev = token;
		token = token->next;
	}
}
*/
static void	is_expanded(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			token->expanded = EXPANDED;
			break ;
		}
		i++;
	}
}

static void	process_redirection(t_token *token)
{
	if (token->type == RED_OUT)
	{
		token->next->type = OUT_FILE;
		is_expanded(token->next);
	}
	else if (token->type == RED_IN)
	{
		token->next->type = IN_FILE;
		is_expanded(token->next);
	}
	else if (token->type == APPEND)
	{
		token->next->type = APP_FILE;
		is_expanded(token->next);
	}
	else if (token->type == HERE_DOC)
		token->next->type = DELIMITER;
}

static void specify_word(t_token *token, t_token *prev)
{
    if (prev->type == CMD || prev->type == BUILTIN)
	{
		if(prev->next && !strcmp(prev->value, "export"))
			token->exp = EXPORT;
        token->type = ARG;
	}
    else
        token->type = CMD;
}

void	lexing(t_token *token)
{
	t_token	*prev;

	if (token && token->type == WORD)
	{
		if (is_builtin(token->value))
		{
			if(token->next && !strcmp(token->value, "export"))
				token->next->exp = EXPORT;
			token->type = BUILTIN;
		}
		else
			token->type = CMD;
		prev = token;
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
