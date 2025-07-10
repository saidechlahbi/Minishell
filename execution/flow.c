/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:14:17 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/10 00:43:29 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int count_args_of_cmd(t_token *token)
{
    int count;
    
    count = 0;
    while (token && token->type != PIPE)
    {
        if (token->type == CMD || token->type == BUILTIN || token->type == ARG)
            count++;
        token = token->next;
    }
    return count;
}

static char **fill_cmd(t_token *token)
{
    char **cmd;
    int count;
    
    cmd = NULL;
    if (count_args_of_cmd(token) == 0)
        return NULL;
    cmd = malloc(sizeof(char *) * (count_args_of_cmd(token) + 1));
    if (!cmd)
        exit(1);
    count = 0;
    while (token && token->type != PIPE)
    {
        if (token->type == CMD || token->type == BUILTIN)
            cmd[count++] = token->value;
        if (token->type == ARG)
            cmd[count++] = token->value;
        token = token->next;
    }
    cmd[count] = NULL;
    return cmd;
}

static t_redirection *get_redirec(t_token *token)
{
    t_redirection *redirec;
    t_redirection *red_tmp;

    redirec = NULL;
    while (token && token->type != PIPE)
    {
        red_tmp = NULL;
        if (token->type == RED_IN || token->type == APPEND 
            || token->type == RED_OUT)
        {
            red_tmp = malloc(sizeof(t_redirection));
            if (!red_tmp)
                exit(1);
            red_tmp->file = token->next->value;
            red_tmp->type = token->next->type;
            red_tmp->next = NULL;
            token = token->next->next;
        }
        else if (token->type == HERE_DOC)
        {
            red_tmp = malloc(sizeof(t_redirection));
            if (!red_tmp)
                exit(1);
            red_tmp->file = randomize();
            red_tmp->delimiter = token->next->value;
            red_tmp->type = token->type;
            red_tmp->next = NULL;
            token = token->next->next;
        }
        else
            token = token->next;
        if (red_tmp)
            add_back_for_redirec(&redirec, red_tmp);
    }
    return redirec;
}

t_cmds *splinting_into_proccess(t_token *token)
{
    t_cmds *commands;
    t_cmds *cmd_tmp;

    commands = NULL;
    while (token)
    {

        cmd_tmp = malloc(sizeof(t_cmds));
        if (!cmd_tmp)
            exit(1);
        cmd_tmp->type = token->type;
        cmd_tmp->cmd = fill_cmd(token);
        cmd_tmp->next = NULL;
        cmd_tmp->redirection = get_redirec(token);
        while (token && token->type != PIPE)
            token = token->next;
        if (token)
            token = token->next;
        add_back_for_cmd(&commands, cmd_tmp);
    }
    return commands;
}
