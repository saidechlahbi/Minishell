/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:29:00 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/11 15:20:53 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_cleaner	*new_cleaner(void *content, t_cleaner *garbage)
{
	t_cleaner	*now;

	now = (t_cleaner *)malloc(sizeof(t_cleaner));
	if (!now)
		get_out_from_here(garbage, 1);
	now->data = content;
	now->next = NULL;
	return (now);
}

static t_cleaner	*last_for_cleaner(t_cleaner *lst)
{
    t_cleaner	*tmp;

    tmp = lst;
    if (!lst)
        return (NULL);
    while (tmp->next != NULL)
        tmp = tmp->next;
    return (tmp);
}

void	add_back_for_cleaner(t_cleaner **lst, t_cleaner *new)
{
	t_cleaner	*tmp;

	if (!new)
		return;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	tmp = last_for_cleaner((*lst));
	tmp->next = new;
}

void get_out_from_here(t_cleaner *garbage, int status)
{
    t_cleaner *tmp;

    tmp = garbage;
    while (tmp)
    {
        free(tmp->data);
        tmp = tmp->next;
    }
    while (garbage)
    {
        tmp = garbage->next;
        free(garbage);
        garbage = tmp;  
    }
    exit(status);
}

void *ft_malloc(size_t type, size_t size, t_cleaner *garbadge)
{
    void *data;

    data = ft_calloc(size, type);
    if (!data)
        get_out_from_here(garbadge, 1);
    add_back_for_cleaner(&garbadge, new_cleaner(data, garbadge));
    return data;
}