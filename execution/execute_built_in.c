/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:19:50 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/19 22:08:05 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_which_built_are(char *cmd)
{
    char *built_in[8];
    int i;

    built_in[0] = "echo";
    built_in[1] = "cd";
    built_in[2] = "pwd";
    built_in[3] = "export";
    built_in[4] = "unset";
    built_in[5] = "env";
    built_in[6] = "exit";
    built_in[7] = NULL;


    i = 0;
    while (built_in[i])
    {
        if (ft_strcmp(built_in[i], cmd) == 0)
            return i;
        i++;
    }
    return 0;
}

void 	execute_built_in(char **cmd, t_env **env, t_garbage **garbage)
{
    int checker;

    (void)garbage;
    (void)env;
    checker = check_which_built_are(cmd[0]);
    if (checker == 0)
        ft_echo(cmd);
        // else if (checker == 1)
        //     ft_cd(cmd);
    else if (checker == 2)
        ft_pwd();
    else if (checker == 3)
        export(env, cmd, garbage);
    else if (checker == 4)
        unset(env, cmd, *garbage);
    else if (checker == 5)
        print_env(*env);
    // else if (checker == 6)
    //     ft_exit(cmd);
    return ;
}