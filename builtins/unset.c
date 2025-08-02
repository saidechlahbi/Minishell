/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:12 by schahir           #+#    #+#             */
/*   Updated: 2025/08/02 15:13:19 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_garbage	*find_node(void *to_find, t_garbage *garbage)
{
	while (garbage)
	{
		if (to_find == garbage->data)
			return (garbage);
		garbage = garbage->next;
	}
	return (NULL);
}

static void	mark_garbage(t_env *node, t_garbage *garbage)
{
	t_garbage	*tmp;

	tmp = find_node(node, garbage);
	if (tmp)
		tmp->var = 0;
	if (node->key)
	{
		tmp = find_node(node->key, garbage);
		if (tmp)
			tmp->var = 0;
	}
	if (node->value)
	{
		tmp = find_node(node->value, garbage);
		if (tmp)
			tmp->var = 0;
	}
}

void	unset(t_env **env, char **args, t_garbage *garbage)
{
	int		i;
	t_env	*cur;
	t_env	*prev;

	i = 1;
	while (args[i])
	{
		prev = NULL;
		cur = *env;
		while (cur)
		{
			if (cur->key && !ft_strcmp(cur->key, args[i]))
			{
				mark_garbage(cur, garbage);
				if (prev == NULL)
					*env = cur->next;
				else
					prev->next = cur->next;
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
}
