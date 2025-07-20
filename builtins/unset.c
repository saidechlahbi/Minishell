/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:12 by schahir           #+#    #+#             */
/*   Updated: 2025/07/21 00:28:22 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_garbage	*find_node(void *to_find, t_garbage *garbage)
{
	while (garbage)
	{
		if (to_find == garbage->data)
			return garbage ;
		garbage = garbage->next;
	}
	return NULL;
}

void	unset_helper(t_env **env, t_garbage *garbage, char *str)
{
    t_env *cur;
    t_env *prev;
	t_garbage *tmp;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		tmp = NULL;
		if (!strcmp(cur->key, str))
		{
			tmp = find_node(cur, garbage);
			if (tmp)
				tmp->var = 0;
			tmp = find_node(cur->key, garbage);
			if (tmp)
				tmp->var = 0;
			tmp = find_node(cur->value, garbage);
			if (tmp)
				tmp->var = 0;
			if (prev == NULL)
				*env = cur->next;
			else
				prev->next = cur->next;
			cur = cur->next;
		}
		prev = cur;
		cur = cur->next;
	}
}

void unset(t_env **env, char **args, t_garbage *garbage)
{
    int i;

	i = 1;
    while (args[i])
    {
		unset_helper(env, garbage, args[i]);
        i++;
    }
}
