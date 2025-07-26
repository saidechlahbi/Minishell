/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:56:46 by schahir           #+#    #+#             */
/*   Updated: 2025/07/15 17:34:07 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2, t_garbage **garbage)
{
	char	*str;

	if (!s1 || !s2)
		return (0);
	str = ft_malloc(1, (ft_strlen(s1) + ft_strlen(s2) + 1), garbage);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	str[ft_strlen(str)] = 0;
	return (str);
}

char	*ft_strdup(const char *src, t_garbage **garbage)
{
	char	*dest;

	dest = ft_malloc(ft_strlen(src) + 1, 1, garbage);
	ft_strcpy(dest, src);
	return (dest);
}
