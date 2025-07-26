/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:57:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/26 22:54:58 by sechlahb         ###   ########.fr       */
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

static char	*get_right_path(t_env *env, char *cmd, t_garbage **garbage)
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
			if (!access(cmd_with_path, X_OK))
				return (cmd_with_path);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd_with_path, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			get_out_from_here(*garbage, 126);
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
		commands->old_cmd = commands->cmd[0];
		if (commands->cmd[0][0] == 0)
			return (commands->executable = 0, 1);
		if (ft_strchr(commands->cmd[0], '/'))
			commands->slash = 1;
		if (ft_strchr(commands->cmd[0], '/') && !access(commands->cmd[0], F_OK))
		{
			commands->executable = (!access(commands->cmd[0], X_OK));
			return (commands->finde = 1, 1);
		}
		cmd = get_right_path(env, commands->cmd[0], garbage);
		if (cmd)
		{
			commands->old_cmd = commands->cmd[0];
			commands->cmd[0] = cmd;
			commands->executable = 1;
		}
	}
	return 0;
}
