/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:01 by schahir           #+#    #+#             */
/*   Updated: 2025/07/25 21:08:25 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*find_key(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	save_data(t_garbage *garbage)
{
	if (!garbage)
		return ;
	while (garbage->next)
		garbage = garbage->next;
	if (garbage)
		garbage->var = 1;
}

int	export_error(char *arg)
{
	int	i;

	i = 0;
	if (is_expandable(arg[i]))
		while (arg[i] && is_expandable2(arg[i]))
			i++;
	if (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			i += 2;
		else if (arg[i] == '=')
			i++;
		else
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			set_status(1);
			return (1);
		}
	}
	return (0);
}
