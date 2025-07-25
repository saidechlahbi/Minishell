
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

int		g_global_signal = 0;

void	handle_sigint(int signum __attribute__((unused)))
{
	if (g_global_signal == 0)
	{
		rl_replace_line("", 0); // Clear the current input
		write(1, "\n", 1);      // Move to new line
		rl_on_new_line();       // Tell readline we're on a new line
		rl_redisplay();         // Redraw the prompt
	}
	else
		write(1, "\n", 1);
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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <limits.h>

// ANSI color codes
#define GREEN   "\001\033[1;32m\002"
#define BLUE    "\001\033[1;34m\002"
#define YELLOW  "\001\033[1;33m\002"
#define RESET   "\001\033[0m\002"

char *get_username() {
    struct passwd *pw = getpwuid (getuid());
    return pw ? pw->pw_name : "user";
}

char *get_cwd() {
    static char cwd[102];
    return getcwd(cwd, sizeof(cwd));
}

char *build_prompt()
 {
    char *user = get_username();
    char *cwd = get_cwd();

    // Static buffer (enough for typical prompts)
    static char prompt[102 + 100];

    snprintf(prompt, sizeof(prompt),
        GREEN "%s" RESET ":" BLUE "%s" RESET YELLOW " $ " RESET,
        user, cwd);

    return prompt;
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
		char **envp)
{
	t_token		*tokens;
	t_env		*env;
	t_garbage	*garbage;
	char		*input;
	t_token		*tmp;

	g_global_signal = 0;
	garbage = NULL;
	env = get_env(envp, &garbage);
	set_not(garbage);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline(build_prompt());
		if (!input)
		{
			ft_putstr_fd("exiting minishell...\n", 2);
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
		tmp = tokens;
		while (tmp)
		{
			printf("%s\ttype%d\tamb%d\tliteral%d\texpanded%d\n", tmp->value,
				tmp->type, tmp->is_ambg, tmp->has_literal, tmp->expanded);
			tmp = tmp->next;
		}
		f(garbage);
		// close_all_fds_fstat(3);
		free_all(&garbage);
	}
}
