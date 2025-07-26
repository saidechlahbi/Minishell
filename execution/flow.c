/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:14:17 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/26 17:29:32 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_redirection	*initial_herdoc(t_token *token, t_garbage **garbage)
{
	t_redirection	*red_tmp;

	red_tmp = ft_malloc(sizeof(t_redirection), 1, garbage);
	red_tmp->file = randomize(garbage);
	red_tmp->delimiter = ft_strdup(token->next->value, garbage);
	red_tmp->type = token->type;
	red_tmp->inq = token->next->inq;
	red_tmp->next = NULL;
	return (red_tmp);
}

static t_redirection	*fill_redir(t_token *token, t_garbage **garbage)
{
	t_redirection	*red_tmp;

	red_tmp = ft_malloc(sizeof(t_redirection), 1, garbage);
	red_tmp->file = ft_strdup(token->next->value, garbage);
	red_tmp->type = token->next->type;
	red_tmp->is_ambg = token->next->is_ambg;
	red_tmp->next = NULL;
	return (red_tmp);
}

static t_redirection	*get_redirec(t_token *token, t_garbage **garbage)
{
	t_redirection	*redirec;
	t_redirection	*red_tmp;

	redirec = NULL;
	while (token && token->type != PIPE)
	{
		red_tmp = NULL;
		if (token->type == RED_IN || token->type == APPEND
			|| token->type == RED_OUT)
		{
			red_tmp = fill_redir(token, garbage);
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
	return (redirec);
}

static t_cmds	*initial_cmd(t_token *token, t_garbage **garbage, char **envp)
{
	t_cmds	*cmd_tmp;

	cmd_tmp = ft_malloc(sizeof(t_cmds), 1, garbage);
	cmd_tmp->cmd = fill_cmd(token, garbage);
	cmd_tmp->envp = envp;
	cmd_tmp->next = NULL;
	cmd_tmp->redirection = get_redirec(token, garbage);
	return (cmd_tmp);
}

t_cmds	*splinting_into_proccess(t_token *token, char **envp,
		t_garbage **garbage)
{
	t_cmds	*commands;
	t_cmds	*cmd_tmp;

	commands = NULL;
	while (token)
	{
		cmd_tmp = initial_cmd(token, garbage, envp);
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
	return (commands);
}
