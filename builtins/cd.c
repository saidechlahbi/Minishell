/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:31:55 by schahir           #+#    #+#             */
/*   Updated: 2025/07/26 06:52:18 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_oldpwd(t_env **env, char *pwd, char *old, t_garbage **garbage)
{
	char	*tmp;

	tmp = ft_strjoin("PWD=", pwd, garbage);
	export_variable(env, tmp, garbage);
	tmp = ft_strjoin("OLDPWD=", old, garbage);
	export_variable(env, tmp, garbage);
}

static int	change_dir(char **args, t_env **env)
{
	char	*target;
	int		res;

	if (!args[1])
	{
		target = exdoc("HOME", *env);
		return (1);
		res = chdir(target);
	}
	else
		res = chdir(args[1]);
	return (res);
}

static void	free_pwd(char *old, char *pwd)
{
	if (old)
		free(old);
	if (pwd)
		free(pwd);
}

int	ft_cd(char **args, t_env **env, t_garbage **garbage)
{
	char	*pwd;
	char	*old;
	int		res;

	if (args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	old = getcwd(NULL, 0);
	res = change_dir(args, env);
	if (res)
	{
		if (res == -1)
			perror("chdir");
		else if (res == 1)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		if (old)
			free(old);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_putstr_fd("cd: error retrieving current directory", 2),
			free_pwd(old, pwd), 1);
	set_oldpwd(env, pwd, old, garbage);
	return (free_pwd(old, pwd), 0);
}
