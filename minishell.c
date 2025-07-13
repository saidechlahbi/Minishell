
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

void handle_sigint(int signum __attribute__((unused)))
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(int ac __attribute__((unused)), char **av __attribute__((unused)),  char **envp)
{
    t_token *tokens;
    t_env   *env;
    t_garbage *garbage;
    int last_exit_status;

    garbage = NULL;
	env = get_env(envp, garbage);
    signal(SIGINT, handle_sigint);
    rl_catch_signals = 0;
    last_exit_status = 0;
    (void)last_exit_status;
    while (1)
    {
        char *input = readline("minishell$ ");  
        if (!input)
            exit(1);
        if (!input[0])
            continue;
        add_back_for_garbage(&garbage, new_garbage(input, garbage));
        add_history(input);
        
        tokens = tokenize(input, garbage);
        lexing(tokens);
        has_dollar(tokens, env, garbage);
        // if (!tokens)
        //     return 1;
        t_token *tmp = tokens;
        while (tmp)
        {
            printf("%s\ttype:%d\n", tmp->value, tmp->type);
            tmp = tmp->next;
        }
        printf("\n");
        
        //execution(tokens, env, &last_exit_status, garbage);
        free_all(garbage);
        garbage = NULL;
        exit(1);
    }
}
