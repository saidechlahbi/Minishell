/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:57:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/08/01 17:58:39 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**get_paths(t_env *env, t_garbage **garbage)
{
	char	**paths;

	paths = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			paths = ft_split(env->value, ':', garbage);
			return (paths);
		}
		env = env->next;
	}
	return (NULL);
}

int	check(char *str)
{
	char	*bin;
	int		i;

	i = 0;
	bin = "bin";
	while (str[i])
	{
		if (str[i] == bin[i])
		{
			if (ft_strncmp(&str[i], bin, 3) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

static int	_is_it_dir(char *cmd)
{
	struct stat	stat_dir;

	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '/'))
		if (!stat(cmd, &stat_dir))
			if (S_ISDIR(stat_dir.st_mode))
				return (1);
	return (0);
}

static char	*get_right_path(t_env *env, char *cmd, t_garbage **garbage,
		t_cmds *commands)
{
	char	**paths;
	char	*cmd_with_path;
	char	*str;

	paths = get_paths(env, garbage);
	if (!paths)
		return (NULL);
	while (*paths)
	{
		str = ft_strjoin(*paths, "/", garbage);
		cmd_with_path = ft_strjoin(str, cmd, garbage);
		if (!access(cmd_with_path, F_OK))
		{
			commands->finde = 1;
			commands->for_no_executable = cmd_with_path;
			if (!access(cmd_with_path, X_OK) && _is_it_dir(cmd_with_path) != 1)
				return (cmd_with_path);
		}
		paths++;
	}
	return (NULL);
}

int	fill_by_path(t_cmds *commands, t_env *env, t_garbage **garbage)
{
	char	*cmd;

	if (commands->cmd && commands->type == CMD)
	{
		if (commands->cmd[0][0] == 0)
			return (commands->executable = 0, 1);
		if (ft_strchr(commands->cmd[0], '/'))
		{
			commands->slash = 1;
			commands->executable = (!access(commands->cmd[0], X_OK));
			return (1);
		}
		cmd = get_right_path(env, commands->cmd[0], garbage, commands);
		if (cmd)
			return (commands->cmd[0] = cmd, commands->executable = 1, 1);
		if (commands->finde)
			commands->cmd[0] = commands->for_no_executable;
		if (_is_it_dir(commands->for_no_executable) == 1)
			return (commands->finde = 0, 1);
	}
	return (0);
}
