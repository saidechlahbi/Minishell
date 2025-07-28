/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:01 by schahir           #+#    #+#             */
/*   Updated: 2025/07/28 17:59:47 by sechlahb         ###   ########.fr       */
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
	while (garbage)
	{
		garbage->var = 1;
		garbage = garbage->next;
	}
}

static void	print_error(char *arg)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	export_error(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '=')
		return (print_error(arg), 1);
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
			return (print_error(arg), 1);
	}
	return (0);
}
