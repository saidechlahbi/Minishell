/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:31:55 by schahir           #+#    #+#             */
/*   Updated: 2025/08/05 14:56:42 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_oldpwd(t_env **env, char *pwd, char *old, t_garbage **garbage)
{
	char	*tmp;

	if (pwd)
	{
		tmp = ft_strjoin("PWD=", pwd, garbage);
		export_variable(env, tmp, garbage);
	}
	if (old)
	{
		tmp = ft_strjoin("OLDPWD=", old, garbage);
		export_variable(env, tmp, garbage);
	}
}

static int	change_dir(char **args, t_env **env)
{
	char	*target;
	int		res;

	if (!args[1])
	{
		target = exdoc("HOME", *env);
		if (!target)
			return (1);
		res = chdir(target);
		if (res)
			return (1);
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

static void	protect_chdir(int res)
{
	if (res == -1)
		perror("chdir");
	else if (res == 1)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
}

int	ft_cd(char **args, t_env **env, t_garbage **garbage)
{
	char	*pwd;
	char	*old;
	int		res;

	old = NULL;
	pwd = NULL;
	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	old = getcwd(NULL, 0);
	res = change_dir(args, env);
	if (res)
		return (protect_chdir(res), free_pwd(old, pwd), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		perror("getcwd: cannot access parent directories");
		return (free_pwd(old, pwd), 1);
	}
	set_oldpwd(env, pwd, old, garbage);
	return (free_pwd(old, pwd), 0);
}
