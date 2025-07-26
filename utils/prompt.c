/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:01:30 by schahir           #+#    #+#             */
/*   Updated: 2025/07/26 17:46:45 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*set_color(char *prompt, char *user, char *pwd, t_garbage **garbage)
{
	prompt = ft_strjoin(prompt, user, garbage);
	prompt = ft_strjoin(prompt, RESET, garbage);
	prompt = ft_strjoin(prompt, ":", garbage);
	prompt = ft_strjoin(prompt, BLUE, garbage);
	prompt = ft_strjoin(prompt, pwd, garbage);
	prompt = ft_strjoin(prompt, RESET, garbage);
	prompt = ft_strjoin(prompt, YELLOW, garbage);
	prompt = ft_strjoin(prompt, " $ ", garbage);
	prompt = ft_strjoin(prompt, RESET, garbage);
	return (prompt);
}

char	*custom_prompt(t_env *env, t_garbage **garbage)
{
	char	*user;
	char	*pwd;
	char	*cwd;
	char	*prompt;

	user = exdoc("USER", env);
	pwd = exdoc("PWD", env);
	cwd = NULL;
	prompt = ft_strdup(GREEN, garbage);
	if (!user)
		user = "user";
	if (!pwd)
	{
		cwd = getcwd(NULL, 0);
		pwd = cwd;
	}
	if (!pwd)
		pwd = "/";
	prompt = set_color(prompt, user, pwd, garbage);
	if (cwd)
		free(cwd);
	return (prompt);
}
