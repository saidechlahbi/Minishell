/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:01 by schahir           #+#    #+#             */
/*   Updated: 2025/08/02 15:15:26 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*create_node(t_env *env, t_garbage **garbage)
{
	t_env	*new_node;

	new_node = ft_malloc(sizeof(t_env), 1, garbage);
	new_node->key = ft_malloc(ft_strlen(env->key) + 1, 1, garbage);
	ft_strncpy(new_node->key, env->key, ft_strlen(env->key));
	new_node->key[ft_strlen(env->key)] = '\0';
	if (env->value)
	{
		new_node->value = ft_malloc(ft_strlen(env->value) + 1, 1, garbage);
		ft_strncpy(new_node->value, env->value, ft_strlen(env->value));
		new_node->value[ft_strlen(env->value)] = '\0';
	}
	else
		new_node->value = NULL;
	return (new_node);
}

static t_env	*create_copy(t_env *env, t_garbage **garbage)
{
	t_env	*new_node;
	t_env	*head;
	t_env	*tail;

	head = NULL;
	tail = NULL;
	while (env)
	{
		new_node = create_node(env, garbage);
		new_node->next = NULL;
		if (!head)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		env = env->next;
	}
	return (head);
}

static void	swap_kv(t_env *cur)
{
	char	*kc;
	char	*vc;

	kc = cur->key;
	cur->key = cur->next->key;
	cur->next->key = kc;
	vc = cur->value;
	cur->value = cur->next->value;
	cur->next->value = vc;
}

static t_env	*sort_export(t_env *head)
{
	int		sorted;
	t_env	*cur;

	if (!head)
		return (NULL);
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		cur = head;
		while (cur && cur->next)
		{
			if (ft_strcmp(cur->key, cur->next->key) > 0)
			{
				swap_kv(cur);
				sorted = 0;
			}
			cur = cur->next;
		}
	}
	return (head);
}

void	print_export(t_env *env, t_garbage **garbage)
{
	t_env	*copy;
	int		i;

	copy = create_copy(env, garbage);
	copy = sort_export(copy);
	while (copy)
	{
		printf("declare -x %s", copy->key);
		if (copy->value)
		{
			printf("=\"");
			i = 0;
			while (copy->value[i])
			{
				printf("%c", copy->value[i]);
				i++;
			}
			printf("\"");
		}
		printf("\n");
		copy = copy->next;
	}
}
