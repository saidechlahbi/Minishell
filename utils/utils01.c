/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:56:20 by schahir           #+#    #+#             */
/*   Updated: 2025/07/18 18:36:45 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_expandable(char c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95);
}

int	is_expandable2(char c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48
			&& c <= 57) || c == 95);
}

char	*_substr(char *str, int start, int len, t_garbage **garbage)
{
	char	*res;

	res = ft_malloc(len + 1, 1, garbage);
	ft_strncpy(res, str + start, len);
	res[len] = 0;
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
