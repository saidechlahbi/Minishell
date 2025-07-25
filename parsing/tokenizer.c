/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:46:25 by schahir           #+#    #+#             */
/*   Updated: 2025/07/25 21:17:35 by schahir          ###   ########.fr       */
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

t_token	*tokenize(char *input, t_garbage **garbage)
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
		set_status(2);
		return (NULL);
	}
	return (var.tokens);
}
