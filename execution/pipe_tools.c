/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:36:18 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/26 06:42:29 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipes(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}

int	check_if_is_it_dir(char *cmd)
{
	struct stat	stat_dir;

	if (ft_strchr(cmd, '/'))
	{
		if (!stat(cmd, &stat_dir))
		{
			if (S_ISDIR(stat_dir.st_mode))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd(": Is a directory\n", 2);
				return (126);
			}
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (127);
		}
	}
	return (0);
}

void	execution_cmd(t_cmds *command, t_env **env, t_garbage **garbage)
{
	int	status;

	if (command->type == BUILTIN)
	{
		status = execute_built_in(command, env, garbage);
		get_out_from_here(*garbage, status);
	}
	else
	{
		execve(command->cmd[0], command->cmd, command->envp);
		perror("execve");
		get_out_from_here(*garbage, 1);
	}
	return ;
}

void	open_and_red_and_fill(t_cmds *command, t_env *env, t_garbage **garbage)
{
	if (redirection(command) == FALSE)
		get_out_from_here(*garbage, 1);
	if (check_if_is_it_dir(command->cmd[0]) == 126)
		get_out_from_here(*garbage, 126);
	else if (check_if_is_it_dir(command->cmd[0]) == 127)
		get_out_from_here(*garbage, 127);
	fill_by_path(command, env, garbage);
	if (command->executable == 0 && command->type == CMD)
	{
		ft_putstr_fd(command->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		get_out_from_here(*garbage, 127);
	}
}

int	ft_size(t_cmds *commands)
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
