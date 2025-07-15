/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:28 by schahir           #+#    #+#             */
/*   Updated: 2025/07/15 17:25:18 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*randomize(t_garbage **garbage)
{
	char	buffer[200];
	char	*str;
	int		i;
	int		j;
	int		fd;

	i = 0;
	j = 0;
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	read(fd, buffer, 200);
	str = ft_malloc(20, 1, garbage);
	while (j < 19)
	{
		if (i >= 200)
		{
			read(fd, buffer, 200);
			i = 0;
		}
		if (ft_isalnum(buffer[i]))
			str[j++] = buffer[i];
		i++;
	}
	str[j] = '\0';
	close(fd);
	return (str);
}
