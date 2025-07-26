/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils05.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:51:34 by schahir           #+#    #+#             */
/*   Updated: 2025/07/25 03:25:55 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i--;
	}
	return (0);
}

static int	ft_wordlen(const char *str, char d)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != d)
		len++;
	return (len);
}

static int	ft_wordcount(const char *str, char d)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == d)
			str++;
		if (*str)
			count++;
		while (*str && *str != d)
			str++;
	}
	return (count);
}

static char	*ft_worddup(const char *str, char d, t_garbage **garbage)
{
	int		len;
	char	*copy;

	if (!str)
		return (NULL);
	len = ft_wordlen(str, d);
	copy = ft_malloc(len + 1, 1, garbage);
	ft_strlcpy(copy, str, len + 1);
	return (copy);
}

char	**ft_split(char const *s, char c, t_garbage **garbage)
{
	char	**strs;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	strs = ft_malloc(sizeof(char *), ft_wordcount(s, c) + 1, garbage);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			strs[i] = ft_worddup(s, c, garbage);
			if (!strs[i])
				get_out_from_here(*garbage, 1);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	strs[i] = NULL;
	return (strs);
}
