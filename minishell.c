
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

void handle_sigint(int signum)
{
    (void)signum;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(int ac __attribute__((unused)), char **av __attribute__((unused)),  char **envp)
{
    t_token *tokens;
    t_env   *env;
    int last_exit_statis;

	env = get_env(envp);
    signal(SIGINT, handle_sigint);
    rl_catch_signals = 0;
    last_exit_statis = 0;
    while (1)
    {
        char *input = readline("minishell$ ");
        if (!input)
            exit(1);
        if (!ft_strncmp(input, "exit",4))
            exit(0);
        if (!input[0])
            continue;
        add_history(input);
        // if (!ft_strcmp(input, "echo $?"))
        //     printf("%d\n", last_exit_statis);
        tokens = tokenize(input);
        lexing(tokens);
        has_dollar(tokens, env);
        remove_quotes(tokens);
        restore_quotes(tokens);

        execution(tokens, env, &last_exit_statis);
        if (!ft_strncmp(input, "history -c",10))
            rl_clear_history();
    }
}
