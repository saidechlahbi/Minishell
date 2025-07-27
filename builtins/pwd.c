/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:10 by schahir           #+#    #+#             */
/*   Updated: 2025/07/27 19:11:44 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_env *env)
{
	char	*pwd;
	char	*cwd;

	pwd = exdoc("PWD", env);
	cwd = NULL;
	if (!pwd)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (perror("pwd: error retrieving current directory: \
				getcwd: cannot access parent directories: "), 1);
		pwd = cwd;
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	if (cwd)
		free(cwd);
	return (0);
}
