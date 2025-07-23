/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:46:25 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/23 10:57:31 by schahir          ###   ########.fr       */
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

static void	handle_quotes(t_scanner *var, char c)
{
	if (c == '\'' && !var->in_dquote)
	{
		var->in_squote = !var->in_squote;
		var->i++;
	}
	else if (c == '"' && !var->in_squote)
	{
		var->in_dquote = !var->in_dquote;
		var->i++;
	}
}

static void	handle_spaces(t_scanner *var, char *input, t_garbage **garbage)
{
	if (var->i > var->start)
		add_token(&var->tokens, _substr(input, var->start, var->i - var->start,
				garbage), WORD, garbage);
	while (ft_isspace(input[var->i]))
		var->i++;
	var->start = var->i;
}

static void	handle_operator(t_scanner *var, char *input, t_garbage **garbage)
{
	if (var->i > var->start)
		add_token(&var->tokens, _substr(input, var->start, var->i - var->start,
				garbage), WORD, garbage);
	else if (is_append(&input[var->i]) != -1)
	{
		add_token(&var->tokens, _substr(input, var->i, 2, garbage),
			is_append(&input[var->i]), garbage);
		var->i += 2;
	}
	else
	{
		add_token(&var->tokens, _substr(input, var->i, 1, garbage),
			is_operator(input[var->i]), garbage);
		var->i++;
	}
	var->start = var->i;
}

t_token	*tokenize(char *input, t_garbage **garbage, int *status)
{
	t_scanner	var;

	ft_bzero(&var, sizeof(var));
	while (input[var.i])
	{
		if (input[var.i] == '\'' || input[var.i] == '"')
			handle_quotes(&var, input[var.i]);
		else if (!var.in_squote && !var.in_dquote && ft_isspace(input[var.i]))
			handle_spaces(&var, input, garbage);
		else if (!var.in_squote && !var.in_dquote
			&& is_operator(input[var.i]) != -1)
			handle_operator(&var, input, garbage);
		else
			var.i++;
	}
	if (var.i > var.start)
		add_token(&var.tokens, _substr(input, var.start, var.i - var.start,
				garbage), WORD, garbage);
	if (var.in_squote || var.in_dquote)
	{
		ft_putstr_fd("Error : Syntax\n", 2);
		*status = 2;
		return (NULL);
	}
	return (var.tokens);
}
/*t_token	*tokenize(char *input, t_garbage **garbage, int *exit_status)
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
}*/
