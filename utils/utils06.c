/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils06.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:08:55 by schahir           #+#    #+#             */
/*   Updated: 2025/07/19 19:48:51 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_digit(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(long n, t_garbage **garbage)
{
	int		lenght;
	char	*str;

	lenght = count_digit(n);
	str = ft_malloc (lenght + 1, 1 ,garbage);
	str[lenght] = '\0';
	if (n == 0)
		return (str[0] = '0', str);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	lenght--;
	while (n)
	{
		str[lenght--] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
