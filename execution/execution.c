/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:32:53 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/08 11:42:57 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int herdoc_count(t_token *token)
{
    int count;

    count = 0;
    while (token)
    {
        if (token->type == HERE_DOC)
            count++;
        token = token->next;
    }
    return count;
}

void execution(t_token *token)
{
    t_cmds *commands;

    if (herdoc_count(token) >= 17)
    {
        ft_putstr_fd("minishell: maximum here-document count exceeded", 2);
        return ;
    }
    commands = splinting_into_proccess(token);
    if (!commands)
        return ;
    
}