/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:46:25 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/17 14:07:52 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token(t_token **head, char *value, int type, t_garbage **garbage)
{
	t_token	*new;
	t_token	*tmp;

	new = ft_malloc(sizeof(t_token), 1, garbage);
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

int	validate_input(t_token *token, int *status)
{
	t_token	*cur;

	if (!token || !ft_strncmp(token->value, "|", 1))
	{
		ft_putstr_fd("Error : Syntax\n", 2);
		*status = 2;
		return (1);
	}
	cur = token;
	while (cur)
	{
		if ((is_error(cur->value) && cur->next && is_op(cur->next->value))
			|| (is_op(cur->value) && !cur->next))
		{
			ft_putstr_fd("Error : Syntax\n", 2);
			*status = 2;
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

t_token	*tokenize(char *input, t_garbage **garbage, int *exit_status)
{
	t_token	*tokens;
	int		i;
	int		start;
	int		in_squote;
	int		in_dquote;

	tokens = NULL;
	i = 0;
	start = 0;
	in_squote = 0;
	in_dquote = 0;
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
				add_token(&tokens, _substr(input, start, i - start, garbage),
					WORD, garbage);
			i++;
			while (ft_isspace(input[i]))
				i++;
			start = i;
		}
		else if (!in_squote && !in_dquote && is_operator(input[i]) != -1)
		{
			if (i > start)
				add_token(&tokens, _substr(input, start, i - start, garbage),
					WORD, garbage);
			else if (is_append(&input[i]) != -1)
			{
				add_token(&tokens, _substr(input, i, 2, garbage),
					is_append(&input[i]), garbage);
				i += 2;
			}
			else
			{
				add_token(&tokens, _substr(input, i, 1, garbage),
					is_operator(input[i]), garbage);
				i++;
			}
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		add_token(&tokens, _substr(input, start, i - start, garbage), WORD,
			garbage);
	if (in_squote || in_dquote)
	{
		ft_putstr_fd("Error : Syntax\n", 2);
		*exit_status = 2;
		return (NULL);
	}
	return (tokens);
}

void	lexing(t_token *token)
{
	t_token	*prev;

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
		if (token->type == RED_OUT)
			token->next->type = OUT_FILE;
		if (token->type == APPEND)
			token->next->type = APP_FILE;
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

void	delimiter(t_token *token)
{
	int	i;
	int	inq;

	inq = 0;
	while (token)
	{
		if (token->type == DELIMITER)
		{
			i = 0;
			while (token->value[i])
			{
				if (token->value[i] == '\'' || token->value[i] == '"')
					token->inq = 1;
				i++;// konti nassiha
			}
		}
		token = token->next;
	}
}
