/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:33:24 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/16 03:31:59 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_all(t_garbage *garbage)
{
    t_garbage *current = garbage;
    t_garbage *tmp;

    while (current && current->next)
    {
        if (current->next->var == 0)
        {
            tmp = current->next;
            current->next = tmp->next;
            free(tmp->data);
            free(tmp);
        }
        else
            current = current->next;
    }
}

void	get_out_from_here(t_garbage *garbage, int status)
{
	t_garbage	*tmp;

	while (garbage)
	{
		tmp = garbage->next;
		free(garbage->data);
		free(garbage);
		garbage = tmp;
	}
	exit(status);
}
