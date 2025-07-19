/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:29:00 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/17 14:08:23 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_garbage	*new_garbage(void *content, t_garbage *garbage)
{
	t_garbage	*now;

	now = (t_garbage *)malloc(sizeof(t_garbage));
	if (!now)
		get_out_from_here(garbage, 1);
	now->data = content;
	now->var = 0;
	now->next = NULL;
	return (now);
}

static t_garbage	*last_for_garbage(t_garbage *lst)
{
	t_garbage	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	add_back_for_garbage(t_garbage **lst, t_garbage *new)
{
	t_garbage	*tmp;

	if (!new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	tmp = last_for_garbage((*lst));
	tmp->next = new;
}

void	*ft_malloc(size_t type, size_t size, t_garbage **garbage)
{
	void	*data;

	data = ft_calloc(size, type, garbage);
	if (!data)
		get_out_from_here(*garbage, 1);
	add_back_for_garbage(garbage, new_garbage(data, *garbage));
	return (data);
}
