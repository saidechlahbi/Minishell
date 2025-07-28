/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:04 by schahir           #+#    #+#             */
/*   Updated: 2025/07/28 18:01:32 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_var(t_env **head, char *key, char *value, t_garbage **garbage)
{
	t_env	*new;
	t_env	*tmp;

	new = ft_malloc(sizeof(t_env), 1, garbage);
	new->key = key;
	new->value = value;
	new->next = NULL;
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

t_env	*get_env(char **envp, t_garbage **garbage)
{
	t_env	*vars;
	int		i;
	char	*key;
	char	*value;
	char	*equal;

	vars = NULL;
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			key = _substr(envp[i], 0, equal - envp[i], garbage);
			value = ft_strdup(equal + 1, garbage);
			add_var(&vars, key, value, garbage);
		}
		i++;
	}
	return (vars);
}

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
