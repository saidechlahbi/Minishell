/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:01 by schahir           #+#    #+#             */
/*   Updated: 2025/07/26 19:05:46 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	append_value(t_env **env, t_env *node, char *arg,
		t_garbage **garbage)
{
	char	*equal;
	t_env	*existing;

	equal = ft_strchr(arg, '=');
	node->key = _substr(arg, 0, equal - 1 - arg, garbage);
	save_data(*garbage);
	existing = find_key(*env, node->key);
	if (!existing || !existing->value)
		node->value = ft_strdup(equal + 1, garbage);
	else
		node->value = ft_strjoin(existing->value, equal + 1, garbage);
	save_data(*garbage);
}

static void	add_value(t_env *node, char *arg, t_garbage **garbage)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	node->key = _substr(arg, 0, equal - arg, garbage);
	save_data(*garbage);
	node->value = ft_strdup(equal + 1, garbage);
	save_data(*garbage);
}

int	export_variable(t_env **env, char *arg, t_garbage **garbage)
{
	char	*equal;
	t_env	node;
	t_env	*existing;

	if (export_error(arg))
		return (1);
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		node.key = ft_strdup(arg, garbage);
		save_data(*garbage);
		node.value = NULL;
	}
	else if (equal > arg && *(equal - 1) == '+')
		append_value(env, &node, arg, garbage);
	else
		add_value(&node, arg, garbage);
	existing = find_key(*env, node.key);
	if (!existing)
		add_var(env, node.key, node.value, garbage);
	else if (existing && equal)
		existing->value = node.value;
	return (0);
}

int	export(t_env **env, char **args, t_garbage **garbage)
{
	int	i;
	int	status;

	status = 0;
	if (!args[1])
	{
		print_export(*env, garbage);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		status = export_variable(env, args[i], garbage);
		i++;
	}
	return (status);
}
