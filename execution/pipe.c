/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:43:52 by sechlahb          #+#    #+#             */
/*   Updated: 2025/08/02 00:00:38 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	first_pipe(t_cmds *command, t_env **env, int *f_pipe,
		t_garbage **garbage)
{
	command->pid = fork();
	if (command->pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (command->pid == 0)
	{
		if (!command->cmd)
			get_out_from_here(*garbage, 0);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		open_and_red_and_fill(command, *env, garbage);
		if (command->read_from)
			dup2(command->read_from, 0);
		if (command->write_in)
			dup2(command->write_in, 1);
		else
			dup2(f_pipe[1], 1);
		close_all_fds_fstat(3);
		execution_cmd(command, env, garbage);
	}
	return (0);
}

static int	middle_pipe(t_cmds *command, t_env **env, int *f_pipe,
		t_garbage **garbage)
{
	command->pid = fork();
	if (command->pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (command->pid == 0)
	{
		if (!command->cmd)
			get_out_from_here(*garbage, 0);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		open_and_red_and_fill(command, *env, garbage);
		if (command->read_from)
			dup2(command->read_from, 0);
		else
			dup2(f_pipe[0], 0);
		if (command->write_in)
			dup2(command->write_in, 1);
		else
			dup2(f_pipe[1], 1);
		close_all_fds_fstat(3);
		execution_cmd(command, env, garbage);
	}
	return (0);
}

static int	last_pipe(t_cmds *command, t_env **env, int *f_pipe,
		t_garbage **garbage)
{
	command->pid = fork();
	if (command->pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (command->pid == 0)
	{
		if (!command->cmd)
			get_out_from_here(*garbage, 0);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		open_and_red_and_fill(command, *env, garbage);
		if (command->read_from)
			dup2(command->read_from, 0);
		else
			dup2(f_pipe[0], 0);
		if (command->write_in)
			dup2(command->write_in, 1);
		close_all_fds_fstat(3);
		execution_cmd(command, env, garbage);
	}
	return (0);
}

static int	help(t_cmds *cmd, t_env **env, int *f_pipe, t_garbage **garbage)
{
	if (pipe(f_pipe) == -1)
		return (1);
	if (first_pipe(cmd, env, f_pipe, garbage))
		return (kill_proccess(), 1);
	return (0);
}

int	pipes(t_cmds *commands, t_env **env, t_garbage **garbage)
{
	int		f_pipe[2];
	int		s_pipe[2];
	t_cmds	*tmp;

	tmp = commands;
	if (help(commands, env, f_pipe, garbage))
		return (set_status(1), 1);
	tmp = tmp->next;
	while (tmp->next)
	{
		close(f_pipe[1]);
		if (pipe(s_pipe) == -1)
			return (set_status(1), 1);
		f_pipe[1] = s_pipe[1];
		if (middle_pipe(tmp, env, f_pipe, garbage))
			return (kill_proccess(), set_status(1), 1);
		close(f_pipe[0]);
		f_pipe[0] = s_pipe[0];
		f_pipe[1] = s_pipe[1];
		tmp = tmp->next;
	}
	if (last_pipe(tmp, env, f_pipe, garbage))
		return (kill_proccess(), set_status(1), 1);
	close_pipes(f_pipe);
	return (set_status(wait_commands(ft_size(commands), commands, garbage)), 1);
}
