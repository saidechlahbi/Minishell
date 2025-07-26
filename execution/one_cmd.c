/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 03:54:14 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/26 23:15:38 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	execute_cmd(t_cmds *command, int *pid, t_env *env,
		t_garbage **garbage)
{
	*pid = fork();
	if (*pid == -1)
		return (perror("fork failed\n"), 1);
	if (*pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		open_and_red_and_fill(command, env, garbage);
		if (command->read_from)
			dup2(command->read_from, 0);
		if (command->write_in)
			dup2(command->write_in, 1);
		execve(command->cmd[0], command->cmd, command->envp);
		ft_putstr_fd("minishell: ", 2);
		perror(command->old_cmd);
		if (errno == 2)
			get_out_from_here(*garbage, 127);
		if (errno == 13)
			get_out_from_here(*garbage, 126);
		get_out_from_here(*garbage, 1);
	}
	return (0);
}

static int	help(t_cmds *commands)
{
	if (commands->cmd == NULL)
	{
		if (open_files(commands) == FALSE)
		{
			set_status(1);
			return (FALSE);
		}
		set_status(0);
		return (FALSE);
	}
	return (TRUE);
}

int	one_command(t_cmds *commands, t_env **env, t_garbage **garbage)
{
	int	pid;
	int	status;

	if (help(commands) == FALSE)
		return (1);
	if (commands->type == BUILTIN)
	{
		commands->printable = 1;
		execute_cmd_built_in(commands, env, garbage);
	}
	else
	{
		g_global_signal = -1;
		if (execute_cmd(commands, &pid, *env, garbage))
			return (set_status(1), 0);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				write(1, "\n", 1);
			return (set_status(128 + WTERMSIG(status)), 1);
		}
		set_status(WEXITSTATUS(status));
	}
	return (0);
}
