/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:33:24 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/12 16:13:29 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void free_all(t_garbage *garbage)
{
    t_garbage *tmp;

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
}

void get_out_from_here(t_garbage *garbage, int status)
{
    t_garbage *tmp;

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
