/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:31:58 by schahir           #+#    #+#             */
/*   Updated: 2025/07/19 23:10:36 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n)
		write(1, "\n", 1);
}
