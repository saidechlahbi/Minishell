/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:14:17 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/19 22:45:55 by sechlahb         ###   ########.fr       */
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

static char **fill_cmd(t_token *token, t_garbage **garbage)
{
    char **cmd;
    int count;
    
    cmd = NULL;
    if (count_args_of_cmd(token) == 0)
        return NULL;
    cmd = ft_malloc(sizeof(char *), (count_args_of_cmd(token) + 1), garbage);
    count = 0;
    while (token && token->type != PIPE)
    {
        if (token->type == CMD || token->type == BUILTIN)
        {
            cmd[count] = ft_strdup(token->value, garbage);
            count++;
        }
        if (token->type == ARG)
        {
            cmd[count] = ft_strdup(token->value, garbage);
            count++; 
        }
        token = token->next;
    }
    cmd[count] = NULL;
    return cmd;
}

static t_redirection *initial_herdoc(t_token *token, t_garbage **garbage)
{
    t_redirection *red_tmp;

    red_tmp = ft_malloc(sizeof(t_redirection), 1, garbage);
    red_tmp->file = randomize(garbage);
    red_tmp->delimiter = ft_strdup(token->next->value, garbage);
    red_tmp->type = token->type;
    red_tmp->inq = token->next->inq;
    red_tmp->next = NULL;
    return red_tmp;
}

static t_redirection *get_redirec(t_token *token, t_garbage **garbage)
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
            red_tmp = ft_malloc(sizeof(t_redirection), 1, garbage);
            red_tmp->file = ft_strdup(token->next->value, garbage);
            red_tmp->type = token->next->type;
            red_tmp->next = NULL;
            token = token->next->next;
        }
        else if (token->type == HERE_DOC)
        {
            red_tmp = initial_herdoc(token, garbage);
            token = token->next->next;
        }
        else
            token = token->next;
        if (red_tmp)
            add_back_for_redirec(&redirec, red_tmp);
    }
    return redirec;
}

t_cmds *splinting_into_proccess(t_token *token, char **envp, t_garbage **garbage)
{
    t_cmds *commands;
    t_cmds *cmd_tmp;

    commands = NULL;
    while (token)
    {

        cmd_tmp = ft_malloc(sizeof(t_cmds), 1, garbage);
        
        cmd_tmp->cmd = fill_cmd(token, garbage);
        cmd_tmp->envp = envp;
        cmd_tmp->next = NULL;
        cmd_tmp->redirection = get_redirec(token, garbage);
        while (token && token->type != PIPE)
        {
            if (token->type == BUILTIN || token->type == CMD)
                cmd_tmp->type = token->type;
            token = token->next;
        }
        if (token)
            token = token->next;
        add_back_for_cmd(&commands, cmd_tmp);
    }
    return commands;
}
