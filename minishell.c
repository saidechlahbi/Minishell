
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

int main(int ac __attribute__((unused)), char **av __attribute__((unused)),  char **envp)
{
    t_token *tokens;
    t_token *tmp;
    t_env   *env;
    t_cmds *commands;

	env = get_env(envp);
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

        tokens = tokenize(input);
        lexing(tokens);
        has_dollar(tokens, env);
        remove_quotes(tokens);
        restore_quotes(tokens);
        // if (!tokens)
        //     return 1;
        tmp = tokens;
        while (tmp)
        {
            printf("%s\ttype:%d\n", tmp->value, tmp->type);
            tmp = tmp->next;
        }
        printf("\n");

        commands = splinting_into_proccess(token)
        //export(env);
        //print_env(env);
        if (!ft_strncmp(input, "history -c",10))
            rl_clear_history();
    }
    // printf("%s\n",getenv("PATH"));
}
