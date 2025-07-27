/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:32:53 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/27 21:08:12 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**env_lst_to_char2(t_env *env, t_garbage **garbage)
{
	t_env	*tmp;
	char	**envp;
	char	*str;
	int		count;

	tmp = env;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = ft_malloc(sizeof(char *) * (count + 1), 1, garbage);
	count = 0;
	while (env)
	{
		str = ft_strjoin(env->key, "=", garbage);
		envp[count++] = ft_strjoin(str, env->value, garbage);
		env = env->next;
	}
	envp[count] = NULL;
	return (envp);
}

void	execution(t_token *token, t_env **env, t_garbage **garbage)
{
	t_cmds	*commands;
	char	**envp;

	envp = env_lst_to_char2(*env, garbage);
	commands = splinting_into_proccess(token, envp, garbage);
	if (!commands)
		return ;
	if (herdoc(commands, *env, garbage) == FALSE)
	{
		if (set_status(-1) == 130)
			write(2, "\n", 1);
		return ;
	}
	if (commands->next == NULL)
		one_command(commands, env, garbage);
	else
	{
		g_global_signal = -1;
		pipes(commands, env, garbage);
	}
}
