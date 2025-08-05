/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:36:18 by sechlahb          #+#    #+#             */
/*   Updated: 2025/08/05 14:48:07 by schahir          ###   ########.fr       */
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
	t_garbage	*garbage;
	char		*msg;

	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '/'))
	{
		if (!stat(cmd, &stat_dir))
		{
			if (S_ISDIR(stat_dir.st_mode))
			{
				garbage = f(NULL);
				msg = ft_strjoin("minishell: ", cmd, &garbage);
				msg = ft_strjoin(msg, ": Is a directory\n", &garbage);
				ft_putstr_fd(msg, 2);
				return (1);
			}
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
		ft_putstr_fd("minishell: ", 2);
		perror(command->cmd[0]);
		if (errno == 2)
			get_out_from_here(*garbage, 127);
		if (errno == 13)
			get_out_from_here(*garbage, 126);
		get_out_from_here(*garbage, 1);
	}
	return ;
}

void	open_and_red_and_fill(t_cmds *command, t_env *env, t_garbage **garbage)
{
	char	*msg;

	if (redirection(command) == FALSE)
		get_out_from_here(*garbage, 1);
	if (!command->cmd)
		get_out_from_here(*garbage, 0);
	if (check_if_is_it_dir(command->cmd[0]))
		get_out_from_here(*garbage, 126);
	fill_by_path(command, env, garbage);
	if (command->executable == 0 && command->type == CMD && command->finde == 0
		&& command->slash == 0)
	{
		msg = ft_strjoin("minishell: ", command->cmd[0], garbage);
		msg = ft_strjoin(msg, ": command not found\n", garbage);
		ft_putstr_fd(msg, 2);
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
