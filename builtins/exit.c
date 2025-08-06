/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:07:39 by sechlahb          #+#    #+#             */
/*   Updated: 2025/08/06 11:35:49 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static unsigned char	_atoi(const char *str, int *error)
{
	unsigned long long	result;
	int					sign;

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
		result = result * 10 + (*str++ - '0');
		if (sign == 1 && result > LLONG_MAX)
			return (*error = 1, 0);
		if (sign == -1 && result > 9223372036854775808ULL)
			return (*error = 1, 0);
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
	char	*msg;

	if (i == 1)
	{
		msg = ft_strjoin("minishell: exit: ", args, &garbage);
		msg = ft_strjoin(msg, ": numeric argument required\n", &garbage);
		ft_putstr_fd(msg, 2);
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
		help(cmd->cmd[1], 1, garbage);
	get_out_from_here(garbage, exit_s);
	return (0);
}
