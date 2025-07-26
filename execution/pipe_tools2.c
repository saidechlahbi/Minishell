/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:36:18 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/26 03:58:38 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wait_commands(int size, t_cmds *cmd, t_garbage **garbage)
{
	int	i;
	int	*status;

	status = ft_malloc(size, sizeof(int), garbage);
	i = 0;
	while (cmd)
	{
		waitpid(cmd->pid, &status[i], 0);
		cmd = cmd->next;
		i++;
	}
	if (WIFSIGNALED(status[size - 1]))
	{
		if (WTERMSIG(status[size - 1]) == 2)
			write(1, "\n", 1);
		return (WTERMSIG(status[size - 1]) + 128);
	}
	return (WEXITSTATUS(status[size - 1]));
}
