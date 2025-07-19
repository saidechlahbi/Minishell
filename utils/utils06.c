/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils06.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:08:55 by schahir           #+#    #+#             */
/*   Updated: 2025/07/19 18:11:57 by schahir          ###   ########.fr       */
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

char	*ft_itoa(int n)
{
	int		lenght;
	char	*str;
	long	p;

	p = n;
	lenght = count_digit(p);
	str = (char *)malloc (lenght + 1);
	if (!str)
		return (NULL);
	str[lenght] = '\0';
	if (n == 0)
		return (str[0] = '0', str);
	if (p < 0)
	{
		str[0] = '-';
		p = -p;
	}
	lenght--;
	while (p)
	{
		str[lenght--] = (p % 10) + '0';
		p = p / 10;
	}
	return (str);
}
