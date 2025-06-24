/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:14:17 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/24 17:47:32 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_proccess *splinting_into_proccess(t_token *token)
{
    t_proccess *proccess;
    t_proccess *struc;
    t_token *tmp;

    proccess = NULL;
    while (token)
    {
        struc = malloc(sizeof(t_proccess));
        struc->tok = token;
        while (token && token->next->type != PIPE))
            token = token->next;
        if (token->next->type == PIPE)
        {
            tmp = token->next;
            token->next = NULL;
            ft_lst_add_back();
            token = tmp->next->next;
        }
        else
        {
            ft_lst_add_back();
            break;
        }
    }
    return proccess;
}
