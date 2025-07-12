/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:42:14 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/12 00:27:22 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
#include <limits.h>

static int	_atoi(const char *str, unsigned char *exit_value)
{
	long long		result;
    int digit;
	int		signe;

	signe = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';

		if (signe == 1)
		{
			if (result > (LLONG_MAX - digit) / 10)
				return 1;
		}
		else
		{
			// Notice the -LLONG_MIN == LLONG_MAX + 1 → this check is tricky
			if (result > (-(LLONG_MIN + digit)) / 10)
				return 1;
		}

		result = result * 10 + digit;
		str++;
	}
	*exit_value = (unsigned char)(result * signe);
    return 0;
}

static int validity(char *str)
{
    while (*str)
    {
        if(*str < '0' || *str > '9')
            return 1;
        str++;
    }
    return 0;
} 

void ft_exit(t_cmds *command, t_cleaner *garbage)
{
    int size;
    unsigned char exit_value;

    (void)garbage;
    size = 0;
    while (command->cmd[size])
        size++;
    if (validity(command->cmd[1]) || _atoi(command->cmd[1], &exit_value))
    {
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(command->cmd[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        exit (2);
    }
    if (size > 2)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        exit (2);
    }
    exit ((int)exit_value);
}
