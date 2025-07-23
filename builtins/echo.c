/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:31:58 by schahir           #+#    #+#             */
/*   Updated: 2025/07/23 09:11:39 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo_helper(char **args, int i)
{
	ft_putstr_fd(args[i], 1);
	if (args[i + 1])
		write(1, " ", 1);
}

void	ft_echo(char **args)
{
	int	i;
	int	j;
	int	n;

	i = 1;
	n = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '-')
			j++;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j])
			break ;
		n = 1;
		i++;
	}
	while (args[i])
	{
		ft_echo_helper(args, i);
		i++;
	}
	if (!n)
		write(1, "\n", 1);
}
