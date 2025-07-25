/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:33:24 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/25 21:45:28 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(t_garbage **garbage)
{
	t_garbage	*current;
	t_garbage	*prev;
	t_garbage	*next;

	current = *garbage;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (current->var == 0)
		{
			if (prev)
				prev->next = next;
			else
				*garbage = next;
			free(current->data);
			free(current);
		}
		else
			prev = current;
		current = next;
	}
}

void	get_out_from_here(t_garbage *garbage, int status)
{
	t_garbage	*tmp;

	while (garbage)
	{
		if (garbage->data)
			free(garbage->data);
		tmp = garbage->next;
		free(garbage);
		garbage = tmp;
	}
	rl_clear_history();
	exit(status);
}
