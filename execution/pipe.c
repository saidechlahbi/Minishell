/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:43:52 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/27 16:06:00 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	first_pipe(t_cmds *commands, char **env, int *f_pipe)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(f_pipe[1], 1);
		close(f_pipe[1]);
		close(f_pipe[0]);
		execve(commands->cmd[0], commands->cmd, env);
	}
	return ;
}

static void	middle_pipe(t_cmds *commands, char **env, int *f_pipe, int *s_pipe)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(f_pipe[0], 0);
		close(f_pipe[1]);
		close(f_pipe[0]);
		dup2(s_pipe[1], 1);
		close(s_pipe[1]);
		close(s_pipe[0]);
		execve(commands->cmd[0], commands->cmd, env);
	}
}

static void	last_pipe(t_cmds *commands, char **env, int *f_pipe)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(f_pipe[0], 0);
		close(f_pipe[1]);
		close(f_pipe[0]);
		execve(commands->cmd[0], commands->cmd, env);
	}
}

int	lst_size(t_cmds *commands)
{
	int	count;

	count = 0;
	while (commands)
	{
		count++;
		commands = commands->next;
	}
	return (count);
}
void	alone_cmd(t_cmds *commands, char **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(commands->cmd[0], commands->cmd, env);
	}
}

void	pipes(t_cmds *commands, t_env *env)
{
	int f_pipe[2];
	int s_pipe[2];
	char **envp;

	open_files(commands);
	fill_by_path(commands, env);
	envp = env_lst_to_char2(env);
	if (lst_size(commands) == 1)
	{
		alone_cmd(commands, envp);
		wait(NULL);
		return ;
	}
	pipe(f_pipe);
	first_pipe(commands, envp, f_pipe);
	commands = commands->next;
	while (commands->next)
	{
		pipe(s_pipe);
		middle_pipe(commands, envp, f_pipe, s_pipe);
		close(f_pipe[0]);
		close(f_pipe[1]);
		f_pipe[0] = s_pipe[0];
		f_pipe[1] = s_pipe[1];
		commands = commands->next;
	}
	last_pipe(commands, envp, f_pipe);
	close(f_pipe[1]);
	close(f_pipe[0]);
	wait(NULL);
	wait(NULL);
	return ;
}