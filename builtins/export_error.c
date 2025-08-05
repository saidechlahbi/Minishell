/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:01 by schahir           #+#    #+#             */
/*   Updated: 2025/08/05 15:01:12 by schahir          ###   ########.fr       */
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

static void	print_error(char *arg)
{
	char		*msg;
	t_garbage	*garbage;

	garbage = f(NULL);
	msg = ft_strjoin("bash: export: `", arg, &garbage);
	msg = ft_strjoin(msg, "': not a valid identifier\n", &garbage);
	ft_putstr_fd(msg, 2);
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
