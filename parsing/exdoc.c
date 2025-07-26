/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exdoc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:25 by schahir           #+#    #+#             */
/*   Updated: 2025/07/26 01:58:42 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*exdoc(char *var, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(var, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*exdoc_exit_status(t_scanner *var, char *input, char *expanded,
		t_garbage **garbage)
{
	if (input[var->i] == '$' && input[var->i + 1] == '?')
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

char	*prepdoc(char *input, t_env *env, t_garbage **garbage)
{
	char		*expanded;
	char		*value;
	t_scanner	var;

	expanded = ft_strdup("", garbage);
	ft_bzero(&var, sizeof(var));
	while (input[var.i])
	{
		expanded = exdoc_exit_status(&var, input, expanded, garbage);
		if (input[var.i] == '$' && is_expandable(input[var.i + 1]))
		{
			expanded = prep_helper(&var, input, expanded, garbage);
			value = exdoc(_substr(input, var.start, var.i - var.start, garbage),
					env);
			if (value)
				expanded = ft_strjoin(expanded, value, garbage);
			var.start = var.i;
		}
		else
			var.i++;
	}
	if (var.i > var.start)
		expanded = ft_strjoin(expanded, _substr(input, var.start, var.i
					- var.start, garbage), garbage);
	return (expanded);
}
