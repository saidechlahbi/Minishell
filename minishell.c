
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

void	handle_sigint(int signum __attribute__((unused)))
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

t_token	*parsing(char *input, int *status, t_garbage **garbage,
		t_env *env __attribute__((unused)))
{
	t_token	*tokens;

	tokens = tokenize(input, garbage, status);
	if (!tokens)
		return (NULL);
	if (validate_input(tokens, status))
		return (NULL);
	lexing(tokens);
	delimiter(tokens);
	has_dollar(tokens, env, garbage);
	return (tokens);
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
		char **envp)
{
	t_token		*tokens;
	t_env		*env;
	t_garbage	*garbage;
	t_garbage	*garbage_env;
	int			status;
	char		*input;
	t_token		*tmp;

	garbage = NULL;
	garbage_env = NULL;
	env = get_env(envp, &garbage_env);
	signal(SIGINT, handle_sigint);
	rl_catch_signals = 0;
	status = 0;
	while (1)
	{
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
			free_all(garbage);
			garbage = NULL;
			continue ;
		}
		tmp = tokens;
		while (tmp)
		{
			printf("%s\ttype:%d\n", tmp->value, tmp->type);
			tmp = tmp->next;
		}
		printf("\n");
		// print_export(env);
		// execution(tokens, env, &status, garbage);
		free_all(garbage);
		free_all(garbage_env);
		// printf("%d\n", sizee(garbage));
		garbage = NULL;
		exit(1);
	}
}
