/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils05.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:51:34 by schahir           #+#    #+#             */
/*   Updated: 2025/07/15 17:34:39 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_wordlen(const char *str, char d)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != d)
		len++;
	return (len);
}

static int	ft_countwords(const char *str, char d)
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

static char	**ft_free_split(char **strs, int count)
{
	while (count--)
		free(strs[count]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c, t_garbage **garbage)
{
	char	**strs;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	strs = ft_malloc(sizeof(char *), ft_countwords(s, c) + 1, garbage);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			strs[i] = ft_worddup(s, c, garbage);
			if (!strs[i])
				return (ft_free_split(strs, i));
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	strs[i] = NULL;
	return (strs);
}
