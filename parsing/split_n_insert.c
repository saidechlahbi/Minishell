/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_n_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:35 by schahir           #+#    #+#             */
/*   Updated: 2025/08/02 05:02:22 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	skip_spaces(t_scanner *var, char *input)
{
	while (input[var->i] && ft_isspace(input[var->i]))
		var->i++;
	var->start = var->i;
}

static void	to_split(t_scanner *var, char *input, char *encapsulizer)
{
	if (!input[var->i])
		return ;
	if (!ft_strncmp(&input[var->i], encapsulizer, 19))
	{
		var->i += 19;
		var->encapsuled = !var->encapsuled;
	}
	else if (input[var->i] == '\'' && !var->in_dquote && !var->encapsuled)
	{
		var->in_squote = !var->in_squote;
		var->i++;
	}
	else if (input[var->i] == '"' && !var->in_squote && !var->encapsuled)
	{
		var->in_dquote = !var->in_dquote;
		var->i++;
	}
}

int	count_tok(char *input, char *encapsulizer)
{
	int			count;
	t_scanner	var;

	ft_bzero(&var, sizeof(var));
	count = 0;
	while (input[var.i])
	{
		to_split(&var, input, encapsulizer);
		if (!input[var.i])
			break ;
		if (!var.in_squote && !var.in_dquote && ft_isspace(input[var.i]))
		{
			if (var.i > var.start)
				count++;
			skip_spaces(&var, input);
		}
		else
			var.i++;
	}
	if (var.i > var.start)
		count++;
	return (count);
}

char	**str_tok(char *input, char *enc, t_garbage **garbage)
{
	char		**tokens;
	int			j;
	t_scanner	v;

	ft_bzero(&v, sizeof(v));
	tokens = NULL;
	j = 0;
	tokens = ft_malloc(sizeof(char *), (count_tok(input, enc) + 1), garbage);
	while (input[v.i])
	{
		to_split(&v, input, enc);
		if (!input[v.i])
			break ;
		if (!v.in_squote && !v.in_dquote && ft_isspace(input[v.i]))
		{
			if (v.i > v.start)
				tokens[j++] = _substr(input, v.start, v.i - v.start, garbage);
			skip_spaces(&v, input);
		}
		else
			v.i++;
	}
	if (v.i > v.start)
		tokens[j++] = _substr(input, v.start, v.i - v.start, garbage);
	return (tokens[j] = NULL, tokens);
}

int	split_n_insert(t_token *cur, char *enapsulizer, t_garbage **garbage)
{
	char	**splits;
	t_token	*new;
	int		i;

	if (!cur || !cur->value || !cur->value[0])
		return (0);
	splits = str_tok(cur->value, enapsulizer, garbage);
	if (!splits || !splits[0])
		return (cur->value = ft_strdup("", garbage), 0);
	cur->value = ft_strdup(splits[0], garbage);
	cur->type = WORD;
	i = 1;
	while (splits[i])
	{
		new = ft_malloc(sizeof(t_token), 1, garbage);
		new->value = ft_strdup(splits[i], garbage);
		new->type = WORD;
		new->next = cur->next;
		cur->next = new;
		cur = new;
		i++;
	}
	return (0);
}
