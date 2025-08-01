/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:31:58 by schahir           #+#    #+#             */
/*   Updated: 2025/07/29 21:37:29 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_helper(char **args, int i)
{
	ft_putstr_fd(args[i], 1);
	if (args[i + 1])
		write(1, " ", 1);
}

static int	has_option(char *arg)
{
	int	j;

	j = 0;
	if (arg[j] == '-')
	{
		j++;
		while (arg[j] == 'n')
			j++;
		if (!arg[j])
			return (1);
	}
	return (0);
}

void	ft_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (args[i])
	{
		if (has_option(args[i]))
		{
			n = 1;
			i++;
		}
		else
			break ;
	}
	while (args[i])
	{
		ft_echo_helper(args, i);
		i++;
	}
	if (!n)
		write(1, "\n", 1);
}
