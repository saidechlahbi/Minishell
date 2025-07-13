/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:33:24 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/13 17:17:58 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_all(t_garbage *garbage)
{
    t_garbage *tmp;

    while (garbage)
    {
        tmp = garbage->next;
        free(garbage->data);
        free(garbage);
        garbage = tmp;
    }   
}

void get_out_from_here(t_garbage *garbage, int status)
{
    t_garbage *tmp;

    while (garbage)
    {
        tmp = garbage->next;
        free(garbage->data);
        free(garbage);
        garbage = tmp;  
    }
    exit(status);
}
