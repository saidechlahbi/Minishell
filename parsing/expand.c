/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:25 by schahir           #+#    #+#             */
/*   Updated: 2025/07/25 23:32:03 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand(char *var, t_env *env, char *encapsulizer, t_garbage **garbage)
{
	char	*input;
	int		i;

	i = 0;
	while (env)
	{
		if (!ft_strcmp(var, env->key))
		{
			while (env->value[i])
			{
				if (env->value[i] == '\'' || env->value[i] == '"')
				{
					input = ft_strdup(encapsulizer, garbage);
					input = ft_strjoin(input, env->value, garbage);
					input = ft_strjoin(input, encapsulizer, garbage);
					return (input);
				}
				i++;
			}
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

char	*expand_exit_status(t_scanner *var, char *input, char *expanded,
		t_garbage **garbage)
{
	if (input[var->i] == '\'' && !var->in_dquote)
	{
		var->in_squote = !var->in_squote;
		var->has_literal = 1;
	}
	if (input[var->i] == '"' && !var->in_squote)
	{
		var->in_dquote = !var->in_dquote;
		var->has_literal = 1;
	}
	if (input[var->i] == '$' && !var->in_squote && input[var->i + 1] == '?')
	{
		expanded = ft_strjoin(expanded, _substr(input, var->start, var->i
					- var->start, garbage), garbage);
		var->i += 2;
		var->start = var->i;
		expanded = ft_strjoin(expanded, ft_itoa(set_status(-1), garbage),
				garbage);
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

char	*prep(char *input, t_env *env, char *encapsulizer, t_garbage **garbage)
{
	char		*expanded;
	char		*value;
	t_scanner	v;

	ft_bzero(&v, sizeof(v));
	expanded = ft_strdup("", garbage);
	while (input[v.i])
	{
		expanded = expand_exit_status(&v, input, expanded, garbage);
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

void	has_dollar(t_token *tokens, t_env *env, t_garbage **garbage)
{
	t_token	*cur;
	t_token	*next;
	char	*expanded;
	char	*encapsulizer;
	char	*last;

	cur = tokens;
	is_amb(cur, env, garbage);
	encapsulizer = randomize(garbage);
	while (cur)
	{
		next = cur->next;
		cur->has_literal = check_literal(cur->value);
		if (ft_strchr(cur->value, '$') && cur->type != DELIMITER
			&& cur->is_ambg != AMBIGIUOS)
		{
			last = ft_strrchr(cur->value, '$');
			expanded = prep(cur->value, env, encapsulizer, garbage);
			cur->value = expanded;
			if (check_last(last) && cur->exp != EXPORT)
				split_n_insert(cur, encapsulizer, garbage);
		}
		cur = next;
	}
	remove_quotes(tokens, encapsulizer, garbage);
}
