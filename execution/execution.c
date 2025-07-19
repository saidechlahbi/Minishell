/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:32:53 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/19 21:01:43 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int herdoc_count(t_token *token)
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

int size(t_cmds *commands)
{
    int count;

    count = 0;
    while (commands)
    {
        count++;
        commands = commands->next;
    }
    return count;
}

static void seting(t_garbage *garage, int status)
{
    while (garage)
    {
        garage->status = status;
        garage = garage->next;
    }
    return;
}

void execution(t_token *token, t_env **env, int *exit_status, t_garbage **garbage)
{
    t_cmds *commands;
    char **envp;

    envp = env_lst_to_char2(*env, garbage);
    if (herdoc_count(token) >= 17)
    {
        ft_putstr_fd("minishell: maximum here-document count exceeded", 2);
        *exit_status = 2;
        return ;
    }
    commands = splinting_into_proccess(token, envp, garbage);
    if (!commands)
        return ;
    seting(*garbage, *exit_status);
    if (!herdoc(commands, exit_status, *env, garbage))
        return ;
    fill_by_path(commands, *env, garbage);
    if (size(commands) == 1)
        one_command(commands, env, exit_status, garbage);
    else
        pipes(commands, exit_status, env, garbage);
}
