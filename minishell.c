/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/26 04:09:25 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int			g_global_signal = 0;

void	handle_sigint(int signum __attribute__((unused)))
{
	if (g_global_signal == 0)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	g_global_signal = 0;
}

t_token	*parsing(char *input, t_garbage **garbage, t_env *env)
{
	t_token	*tokens;

	tokens = tokenize(input, garbage);
	if (!tokens)
		return (NULL);
	if (validate_input(tokens))
		return (NULL);
	lexing(tokens);
	delimiter(tokens);
	has_dollar(tokens, env, garbage);
	lexing(tokens);
	skip_nodes(&tokens);
	return (tokens);
}

void	set_not(t_garbage *garbage)
{
	while (garbage)
	{
		garbage->var = 1;
		garbage = garbage->next;
	}
	return ;
}

static void	help(t_env **env, t_garbage **garbage, char *input, t_token *tokens)
{
	while (1)
	{
		input = readline(custom_prompt(env, &garbage));
		if (!input)
		{
			ft_putstr_fd("exit\n", 2);
			get_out_from_here(garbage, 1);
		}
		if (!input[0])
			continue ;
		add_back_for_garbage(&garbage, new_garbage(input, garbage));
		add_history(input);
		tokens = parsing(input, &garbage, env);
		if (!tokens)
		{
			free_all(&garbage);
			garbage = NULL;
			continue ;
		}
		f(garbage);
		execution(tokens, &env, &garbage);
		close_all_fds_fstat(3);
		free_all(&garbage);
	}
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
		char **envp)
{
	t_token		*tokens;
	t_env		*env;
	t_garbage	*garbage;
	char		*input;

	g_global_signal = 0;
	garbage = NULL;
	env = get_env(envp, &garbage);
	set_not(garbage);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	help(&env, &garbage, input, tokens);
}
