/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:19:50 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/27 18:49:29 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_built_in(t_cmds *cmd, t_env **env, t_garbage **garbage)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		ft_echo(cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		status = ft_cd(cmd->cmd, env, garbage);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		status = ft_pwd(*env);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		status = export(env, cmd->cmd, garbage);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		unset(env, cmd->cmd, *garbage);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		print_env(*env);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		status = ft_exit(cmd, *garbage);
	return (status);
}

void	execute_cmd_built_in(t_cmds *commands, t_env **env, t_garbage **garbage)
{
	int	std_in;
	int	std_out;
	int	status;

	std_in = dup(0);
	std_out = dup(1);
	if (open_files(commands) == FALSE || std_in == -1 || std_out == -1)
	{
		set_status(1);
		return ;
	}
	redirection(commands);
	if (commands->read_from)
		dup2(commands->read_from, 0);
	if (commands->write_in)
		dup2(commands->write_in, 1);
	status = execute_built_in(commands, env, garbage);
	set_status(status);
	close(0);
	close(1);
	dup(std_in);
	dup(std_out);
	return ;
}
