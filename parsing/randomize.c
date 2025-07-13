/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:28 by schahir           #+#    #+#             */
/*   Updated: 2025/07/13 10:42:23 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *randomize(t_garbage *garbage)
{
    char buffer[200];
    char *str;
    int i = 0;
    int j = 0;

    int fd = open("/dev/random", O_RDONLY);
    if (fd == -1)
        return (NULL);
    read(fd,buffer,200);
    str = ft_malloc(20, 1, garbage);
    while (j < 19)
    {
        if (i >= 200)
        {
            read(fd,buffer,200);
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
