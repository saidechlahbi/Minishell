/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:25 by schahir           #+#    #+#             */
/*   Updated: 2025/07/24 09:36:59 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand(char *var, t_env *env, char *encapsulizer, t_garbage **garbage)
{
	char	*input;

	while (env)
	{
		if (!ft_strcmp(var, env->key))
		{
			input = ft_strdup(encapsulizer, garbage);
			input = ft_strjoin(input, env->value, garbage);
			input = ft_strjoin(input, encapsulizer, garbage);
			return (input);
		}
		env = env->next;
	}
	return (NULL);
}

static char	*expand_exit_status(t_scanner *var, char *input, char *expanded,
		int status, t_garbage **garbage)
{
	if (input[var->i] == '\'' && !var->in_dquote)
		var->in_squote = !var->in_squote;
	if (input[var->i] == '"' && !var->in_squote)
		var->in_dquote = !var->in_dquote;
	if (input[var->i] == '$' && !var->in_squote && input[var->i + 1] == '?')
	{
		expanded = ft_strjoin(expanded, _substr(input, var->start, var->i
					- var->start, garbage), garbage);
		var->i += 2;
		var->start = var->i;
		expanded = ft_strjoin(expanded, ft_itoa(status, garbage), garbage);
	}
	return (expanded);
}

char	*prep_helper(t_scanner *var, char *input, char *expanded,
		t_garbage **garbage)
{
	expanded = ft_strjoin(expanded, _substr(input, var->start, var->i
				- var->start, garbage), garbage);
	var->i++;
	var->start = var->i;
	while (input[var->i] && is_expandable2(input[var->i]))
		var->i++;
	return (expanded);
}

char	*prep(char *input, t_env *env, char *encapsulizer, t_garbage **garbage,
		int status)
{
	char		*expanded;
	char		*value;
	t_scanner	v;

	ft_bzero(&v, sizeof(v));
	expanded = ft_strdup("", garbage);
	while (input[v.i])
	{
		expanded = expand_exit_status(&v, input, expanded, status, garbage);
		if (input[v.i] == '$' && !v.in_squote && is_expandable(input[v.i + 1]))
		{
			expanded = prep_helper(&v, input, expanded, garbage);
			value = expand(_substr(input, v.start, v.i - v.start, garbage), env,
					encapsulizer, garbage);
			if (value)
				expanded = ft_strjoin(expanded, value, garbage);
			v.start = v.i;
		}
		else
			v.i++;
	}
	if (v.i > v.start)
		expanded = ft_strjoin(expanded, _substr(input, v.start, v.i - v.start,
					garbage), garbage);
	return (expanded);
}

void	has_dollar(t_token *tokens, t_env *env, t_garbage **garbage, int status)
{
	t_token	*cur;
	t_token	*next;
	char	*expanded;
	char	*encapsulizer;
	char	*last;

	cur = tokens;
	encapsulizer = randomize(garbage);
	while (cur)
	{
		next = cur->next;
		if (ft_strchr(cur->value, '$') && cur->type != DELIMITER)
		{
			last = ft_strrchr(cur->value, '$');
			expanded = prep(cur->value, env, encapsulizer, garbage, status);
			cur->value = expanded;
			if (last && (last[1] == '?' || is_expandable(last[1])) && cur->exp != EXPORT)
				split_n_insert(cur, encapsulizer, garbage);
		}
		cur = next;
	}
	remove_quotes(tokens, encapsulizer, garbage);
	lexing(tokens);
}
/*
char	*prep(char *input, t_env *env, char *encapsulizer, t_garbage **garbage,
		int status)
{
	int		in_squote;
	int		in_dquote;
	int		i;
	int		start;
	char	*expanded;
	char	*value;

	in_squote = 0;
	in_dquote = 0;
	i = 0;
	start = 0;
	expanded = ft_strdup("", garbage);
	while (input[i])
	{
		if (input[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		if (input[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		if (input[i] == '$' && !in_squote && input[i + 1] == '?')
		{
			expanded = ft_strjoin(expanded, _substr(input, start, i - start,
						garbage), garbage);
			i+=2;
			start = i;
			expanded =ft_strjoin(expanded, ft_itoa(status, garbage), garbage);
		}
		if (input[i] == '$' && !in_squote && is_expandable(input[i + 1]))
		{
			expanded = ft_strjoin(expanded, _substr(input, start, i - start,
						garbage), garbage);
			i++;
			if (is_expandable(input[i]))
			{
				start = i;
				while (input[i] && is_expandable2(input[i]))
					i++;
				value = expand(_substr(input, start, i - start, garbage), env,
						encapsulizer, garbage);
				if (value)
					expanded = ft_strjoin(expanded, value, garbage);
			}
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		expanded = ft_strjoin(expanded, _substr(input, start, i - start,
					garbage), garbage);
	return (expanded);
}
*/