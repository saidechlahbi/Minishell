/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:12 by schahir           #+#    #+#             */
/*   Updated: 2025/07/19 17:54:47 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset(t_env **env, char **args)
{
	t_env	*cur;
	t_env	*prev;
	int i = 1;


	






	
	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (!strcmp(cur->key, args))
		{
			if (prev == NULL)
				*env = cur->next;
			else
				prev->next = cur->next;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
