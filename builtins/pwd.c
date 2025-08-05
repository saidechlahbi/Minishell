/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:10 by schahir           #+#    #+#             */
/*   Updated: 2025/08/05 15:43:32 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char		*pwd;
	char		*msg;
	t_garbage	*garbage;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		perror("getcwd: cannot access parent directories");
		return (1);
	}
	garbage = f(NULL);
	msg = ft_strjoin(pwd, "\n", &garbage);
	ft_putstr_fd(msg, 1);
	return (free(pwd), 0);
}
