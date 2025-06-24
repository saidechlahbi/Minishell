/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:46:25 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/19 16:47:12 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void add_token(t_token **head, char *value, int type)
{
	t_token *new;
	t_token *tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return;
	new->value = value;
	new->next = NULL;
	new->type = type;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void validate_input(t_token *token)
{
	t_token *cur;

	if (!token || !ft_strncmp(token->value, "|", 1))
	{
		ft_putstr_fd("Error : Syntax\n", 2);
		return;
	}
	cur = token;
	while (cur)
	{
		if ((is_op(cur->value) && cur->next && is_op(cur->next->value)) || (is_op(cur->value) && !cur->next))
		{
			ft_putstr_fd("Error : Syntax\n", 2);
			return;
		}
		cur = cur->next;
	}
}

t_token *tokenize(char *input)
{
	t_token *tokens = NULL;
	int i = 0;
	int start = 0;
	int in_squote = 0;
	int in_dquote = 0;

	while (input[i])
	{
		if (input[i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			i++;
		}
		else if (input[i] == '"' && !in_squote)
		{
			in_dquote = !in_dquote;
			i++;
		}
		else if (!in_squote && !in_dquote && ft_isspace(input[i]))
		{
			if (i > start)
				add_token(&tokens, _substr(input, start, i - start), WORD);
			i++;
			while (ft_isspace(input[i]))
				i++;
			start = i;
		}
		else if (!in_squote && !in_dquote && is_operator(input[i]) != -1)
		{
			if (i > start)
				add_token(&tokens, _substr(input, start, i - start), WORD);
			else if (is_append(&input[i]) != -1)
			{
				add_token(&tokens, _substr(input, i, 2), is_append(&input[i]));
				i += 2;
			}
			else
			{
				add_token(&tokens, _substr(input, i, 1), is_operator(input[i]));
				i++;
			}
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		add_token(&tokens, _substr(input, start, i - start), WORD);

	if (in_squote || in_dquote)
	{
		ft_putstr_fd("Error : Syntax\n", 2);
		return NULL;
	}
	validate_input(tokens);
	return tokens;
}

void lexing(t_token *token)
{
	t_token *prev;

	prev = token;
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
		if (token->type == RED_OUT || token->type == APPEND)
			token->next->type = OUT_FILE;
		else if (token->type == RED_IN)
			token->next->type = IN_FILE;
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
