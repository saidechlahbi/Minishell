/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/17 17:14:34 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

    int main(int ac __attribute__((unused)), char **av __attribute__((unused)),  char **envp)
{
    int i;
    t_token *tokens;
    t_token *tmp;
    t_env   *env;

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
        has_dollar(tokens, env);
        remove_quotes(tokens);
        restore_quotes(tokens);
        // if (!tokens)
        //     return 1;
        i = 0;
        tmp = tokens;
        while (tmp)
        {
            printf("%s\n", tmp->value);
            tmp = tmp->next;
            i++;
        }
        printf("\n");
        //export(env);
        print_env(env);
        if (!ft_strncmp(input, "history -c",10))
            rl_clear_history();
    }
    // printf("%s\n",getenv("PATH"));
}
