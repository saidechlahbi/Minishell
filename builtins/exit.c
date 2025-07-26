/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:07:39 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/26 07:50:34 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static unsigned char	_atoi(const char *str, int *error)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LLONG_MAX - (*str - '0')) / 10)
		{
			*error = 1;
			break ;
		}
		result = result * 10 + (*str++ - '0');
	}
	return ((unsigned char)(result * sign));
}

static int	check(char *str)
{
	while ((*str && (*str >= 9 && *str <= 13)) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
		str++;
	while ((*str && (*str >= 9 && *str <= 13)) || *str == 32)
		str++;
	if (*str)
		return (1);
	return (0);
}

static void	help(char *args, int i, t_garbage *garbage)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		get_out_from_here(garbage, 2);
	}
	else
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}

int	ft_exit(t_cmds *cmd, t_garbage *garbage)
{
	int	error;
	int	exit_s;

	error = 0;
	if (cmd->printable)
		ft_putstr_fd("exit\n", 2);
	if (cmd->cmd[1] == NULL)
		get_out_from_here(garbage, set_status(-1));
	if (check(cmd->cmd[1]))
		help(cmd->cmd[1], 1, garbage);
	if (cmd->cmd[2])
	{
		help(cmd->cmd[1], 0, garbage);
		return (1);
	}
	exit_s = _atoi(cmd->cmd[1], &error);
	if (error == 1)
		help(cmd->cmd[1], 0, garbage);
	get_out_from_here(garbage, exit_s);
	return 0;
}
