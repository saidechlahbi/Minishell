/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:43:56 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/21 19:36:15 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void pin(t_cmds *commands, char *file)
{
    t_redirection *red;

    while (commands)
    {
        while (red)
        {
            red = commands->redirection;
            if (ft_strcmp(red->file, file) == 0)
            {
                red->is_ambigious = 1;
                return ;
            }
            red = red->next;
        }
        commands = commands->next;
    }
}

void checking_ambigious(t_token *token, t_cmds *commands)
{
    while (token)
    {
        if (token->type == RED_IN || token->type == APPEND 
            || token->type == RED_OUT)
        {
            if (token->next->is_ambg && token->next->next && token->next->next->is_ambg)
            {
                pin(commands, token->next->value);
                return ;
            }
            else if (!token->next->value  && token->next->expanded)
            {
                pin(commands, token->value);
                return ;
            }
            else if (!token->next->value[0] &&  token->next->expanded)
            {
                pin(commands, token->value);
                return ;
            }
        }
        token = token->next;
    }
}
