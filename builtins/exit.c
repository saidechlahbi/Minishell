/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:07:39 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/23 14:32:45 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static unsigned char    _atoi(const char *str, int *error)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
    if (*str == '-' || *str == '+')
    {
        if ((sign = (*str++ == '-')))
            return -1;
        else
            return 1;
    }
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LLONG_MAX - (*str - '0')) / 10)
		{
			*error = 1;
			break;
		}
		result = result * 10 + (*str++ - '0');
	}
	return ((unsigned char)(result * sign));
}

static int check(char *str)
{
    while ((*str && (*str >= 9 && *str <= 13) )|| *str == 32)
        str++;
    if (*str == '-' || *str == '+')
        str++;
    while (*str && *str >= '0' && *str <= '9')
        str++;
    while ((*str && (*str >= 9 && *str <= 13)) || *str == 32)
        str++;
    if (*str)
        return 1;
    return 0;
}

static int ft_sizee(char **args)
{
    int count ;

    count = 0;
    while (args[count])
        count ++;
    return count ;
}

static void help(char *args)
{
    ft_putstr_fd("minishell\n", 2);
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(args, 2);
    ft_putstr_fd(": numeric argument required\n", 2); 
}

void ft_exit(char **args, int exit_status, t_garbage *garbage)
{
    int error;
    int exit_s; 

    error = 0;
    if (ft_sizee(args) == 1)
        exit(exit_status);
    if (check(args[1]))
    {
        help(args[1]);
        get_out_from_here(garbage, 2);
    }
    if (ft_sizee(args) > 2)
    {
        ft_putstr_fd("minishell\n", 2);
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        get_out_from_here(garbage, 2);
    }
    exit_s = _atoi(args[1], &error);
    if (error == 1)
        help(args[1]);
    get_out_from_here(garbage, exit_s);
}
