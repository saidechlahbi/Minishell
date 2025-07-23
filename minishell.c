
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/19 16:47:01 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int g_global_signal = 0;

void	handle_sigint(int signum __attribute__((unused)))
{
	if (g_global_signal == 0)
	{
		write(1, "\n", 1);              // Move to new line
		rl_on_new_line();              // Tell readline we're on a new line
		rl_replace_line("", 0);       // Clear the current input
		rl_redisplay();              // Redraw the prompt
	}
	else
	{
		// rl_done = 1; 
		write(1, "\n", 1);
	}
	g_global_signal = 0;
}

t_token	*parsing(char *input, int *status, t_garbage **garbage,
		t_env *env)
{
	t_token	*tokens;

	tokens = tokenize(input, garbage, status);
	if (!tokens)
		return (NULL);
	if (validate_input(tokens, status))
		return (NULL);
	lexing(tokens);
	delimiter(tokens);
	has_dollar(tokens, env, garbage, (*garbage)->status);
	return (tokens);
}

void set_not(t_garbage *garbage)
{
	while (garbage)
	{
		garbage->var = 1;
		garbage = garbage->next;
	}
	return ;
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
		char **envp)
{
	t_token		*tokens;
	t_env		*env;
	t_garbage	*garbage;
	int			status;
	char		*input;

	g_global_signal = 0;
	garbage = NULL;
	env = get_env(envp, &garbage);
	set_not(garbage);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	status = 0;
	while (1)
	{
		// reset_terminal();
    	// rl_reset_line_state();
		input = readline("minishell$ ");
		if (!input)
			exit(1);
		if (!input[0])
			continue ;
		add_back_for_garbage(&garbage, new_garbage(input, garbage));
		add_history(input);
		tokens = parsing(input, &status, &garbage, env);
		if (!tokens)
		{
			free_all(&garbage);
			garbage = NULL;
			continue ;
		}
		t_token *tmp=tokens;
		while (tmp)
		{
			printf("%s %d\t%d\t%d\n", tmp->value, tmp->type, tmp->is_ambg, tmp->expanded);
			tmp = tmp->next;
		}
		execution(tokens, &env, &status, &garbage);
		close_all_fds_fstat(3);
		free_all(&garbage);
	}
}
