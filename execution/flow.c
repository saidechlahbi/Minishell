/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:14:17 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/27 15:54:19 by sechlahb         ###   ########.fr       */
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
		return ;
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
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	tmp = last((*lst));
	tmp->next = new;
}

char	**fill_cmd(t_token *token)
{
	char	**cmd;
	int		count;
	t_token	*tmp;

	count = 0;
	cmd = NULL;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == BUILTIN || tmp->type == ARG)
			count++;
		tmp = tmp->next;
	}
	cmd = malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		exit(1);
	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD || token->type == BUILTIN)
		{
			cmd[count] = token->value;
			count++;
		}
		if (token->type == ARG)
		{
			cmd[count] = token->value;
			count++;
		}
		token = token->next;
	}
	cmd[count] = NULL;
	return (cmd);
}

t_cmds	*splinting_into_proccess(t_token *token)
{
	t_redirection	*redirection;
	t_redirection	*red_tmp;
	t_cmds			*commands;
	t_cmds			*cmd_tmp;

	commands = NULL;
	while (token)
	{
		redirection = NULL;
		while (token && token->type != PIPE)
		{
			if (token->type == CMD || token->type == BUILTIN)
			{
				cmd_tmp = malloc(sizeof(t_cmds));
				cmd_tmp->cmd = fill_cmd(token);
				cmd_tmp->type = token->type;
				cmd_tmp->next = NULL;
			}
			else if (token->type == RED_IN || token->type == APPEND
				|| token->type == RED_OUT)
			{
				red_tmp = malloc(sizeof(t_redirection));
				if (!red_tmp)
					exit(1);
				red_tmp->file = token->next->value;
				red_tmp->type = token->next->type;
				red_tmp->delimiter = NULL;
				red_tmp->next = NULL;
				add_back(&redirection, red_tmp);
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
				add_back(&redirection, red_tmp);
			}
			token = token->next;
		}
		if (cmd_tmp && redirection)
			cmd_tmp->redirection = redirection;
		else if (!commands && redirection)
		{
			cmd_tmp = malloc(sizeof(t_cmds));
			cmd_tmp->cmd = NULL;
			cmd_tmp->type = 0;
			cmd_tmp->redirection = redirection;
			cmd_tmp->next = NULL;
		}
		if (cmd_tmp)
			lstadd_back(&commands, cmd_tmp);
		redirection = NULL;
		cmd_tmp = NULL;
		if (token)
			token = token->next;
	}
	return (commands);
}
