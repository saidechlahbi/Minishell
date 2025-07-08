/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:44:53 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/08 11:45:21 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmds	*lstlast(t_cmds *lst)
{
    t_cmds	*tmp;

    tmp = lst;
    if (!lst)
        return (NULL);
    while (tmp->next != NULL)
        tmp = tmp->next;
    return (tmp);
}

void	lstadd_back(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

	if (!new)
		return;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	tmp = lstlast((*lst));
	tmp->next = new;
}

t_redirection	*last(t_redirection *lst)
{
    t_redirection	*tmp;

    tmp = lst;
    if (!lst)
        return (NULL);
    while (tmp->next != NULL)
        tmp = tmp->next;
    return (tmp);
}

void	add_back(t_redirection **lst, t_redirection *new)
{
	t_redirection	*tmp;

	if (!new)
		return;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	tmp = last((*lst));
	tmp->next = new;
}
