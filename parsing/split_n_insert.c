/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_n_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:35 by schahir           #+#    #+#             */
/*   Updated: 2025/07/24 11:14:11 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	skip_spaces(t_scanner *var, char *input)
{
	while (ft_isspace(input[var->i]))
		var->i++;
	var->start = var->i;
}

static void	to_split(t_scanner *var, char *input, char *encapsulizer)
{
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

char	**str_tok(char *input, char *encapsulizer, t_garbage **garbage)
{
	char		**tokens;
	int			j;
	t_scanner	v;

	ft_bzero(&v, sizeof(v));
	tokens = NULL;
	j = 0;
	tokens = ft_malloc(sizeof(char *), (count_tok(input, encapsulizer) + 1),
			garbage);
	while (input[v.i])
	{
		to_split(&v, input, encapsulizer);
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
	tokens[j] = NULL;
	return (tokens);
}

void	split_n_insert(t_token *cur, char *enapsulizer, t_garbage **garbage)
{
	char	**splits;
	t_token	*new;
	int		i;

	if (!cur->value[0])
		return ;
	splits = str_tok(cur->value, enapsulizer, garbage);
	cur->value = ft_strdup(splits[0], garbage);
	cur->type = ARG;
	cur->is_ambg = AMBIGIUOS;
	i = 1;
	while (splits[i])
	{
		new = ft_malloc(sizeof(t_token), 1, garbage);
		new->value = ft_strdup(splits[i], garbage);
		new->type = ARG;
		new->is_ambg = AMBIGIUOS;
		new->next = cur->next;
		cur->next = new;
		cur = new;
		i++;
	}
}
/*
int	count_tok(char *input, char *encapsulizer)
{
	int	i;
	int	start;
	int	count;
	int	in_squote;
	int	in_dquote;
	int	ignore;

	i = 0;
	start = 0;
	count = 0;
	in_squote = 0;
	in_dquote = 0;
	ignore = 0;
	while (input[i])
	{
		if (!ft_strncmp(&input[i], encapsulizer, 19))
		{
			i += 19;
			ignore = !ignore;
		}
		else if (input[i] == '\'' && (!in_dquote && !ignore))
		{
			in_squote = !in_squote;
			i++;
		}
		else if (input[i] == '"' && (!in_squote && !ignore))
		{
			in_dquote = !in_dquote;
			i++;
		}
		else if (!in_squote && !in_dquote && ft_isspace(input[i]))
		{
			if (i > start)
				count++;
			i++;
			while (ft_isspace(input[i]))
				i++;
		}
		else
			i++;
	}
	if (i > start)
		count++;
	return (count);
}

char	**str_tok(char *input, char *encapsulizer, t_garbage **garbage)
{
	int		i;
	int		start;
	int		in_squote;
	int		in_dquote;
	char	**tokens;
	int		j;
	int		ignore;

	start = 0;
	in_squote = 0;
	in_dquote = 0;
	tokens = NULL;
	j = 0;
	ignore = 0;
	i = 0;
	tokens = ft_malloc(sizeof(char *), (count_tok(input, encapsulizer) + 1),
			garbage);
	while (input[i])
	{
		if (!ft_strncmp(&input[i], encapsulizer, 19))
		{
			i += 19;
			ignore = !ignore;
		}
		else if (input[i] == '\'' && (!in_dquote && !ignore))
		{
			in_squote = !in_squote;
			i++;
		}
		else if (input[i] == '"' && (!in_squote && !ignore))
		{
			in_dquote = !in_dquote;
			i++;
		}
		else if (!in_squote && !in_dquote && ft_isspace(input[i]))
		{
			if (i > start)
				tokens[j++] = _substr(input, start, i - start, garbage);
			i++;
			while (ft_isspace(input[i]))
				i++;
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		tokens[j++] = _substr(input, start, i - start, garbage);
	tokens[j] = NULL;
	return (tokens);
}

void	split_n_insert(t_token *cur, char *enapsulizer, t_garbage **garbage)
{
	char	**splits;
	t_token	*new;
	int		i;

	if (!cur->value[0])
		return ;
	splits = str_tok(cur->value, enapsulizer, garbage);
	cur->value = ft_strdup(splits[0], garbage);
	cur->type = ARG;
	cur->is_ambg = AMBIGIUOS;
	i = 1;
	while (splits[i])
	{
		new = ft_malloc(sizeof(t_token), 1, garbage);
		new->value = ft_strdup(splits[i], garbage);
		new->type = ARG;
		new->is_ambg = AMBIGIUOS;
		new->next = cur->next;
		cur->next = new;
		cur = new;
		i++;
	}
}
*/