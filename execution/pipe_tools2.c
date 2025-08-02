/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:36:18 by sechlahb          #+#    #+#             */
/*   Updated: 2025/08/02 05:07:22 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	interupted(int *status, int size, int sig)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (WTERMSIG(status[i]) == sig)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

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
	if (WIFEXITED(status[size - 1]) && interupted(status, size, 2))
		write(2, "\n", 2);
	if (WIFSIGNALED(status[size - 1]))
	{
		if (WTERMSIG(status[size - 1]) == 2)
			return (write(2, "\n", 1), WTERMSIG(status[size - 1]) + 128);
		if (WTERMSIG(status[size - 1]) == 3)
			return (ft_putstr_fd("Quit (core dumped)\n", 2), \
				WTERMSIG(status[size - 1]) + 128);
		return (WTERMSIG(status[size - 1]) + 128);
	}
	return (WEXITSTATUS(status[size - 1]));
}
