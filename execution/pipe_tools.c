/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:36:18 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/19 21:24:09 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execution_cmd(t_cmds *command, t_env **env, t_garbage **garbage)
{
    if (command->type == BUILTIN)
        execute_built_in(command->cmd, env, garbage);
    else
    {
        execve(command->cmd[0], command->cmd, command->envp);
        perror("execve");
        get_out_from_here(*garbage, 1);
    }
    return ;
}

void open_and_redirec(t_cmds *command, t_garbage *garbage)
{
    if (open_files(command) == 0)
        get_out_from_here(garbage, 1);
    if (command->executable == 0)
    {
        printf("%s: command not found\n", command->cmd[0]);
        get_out_from_here(garbage, 127);
    }
    redirection(command);
}

int ft_size(t_cmds *commands)
{
    int count;

    count = 0;
    while (commands)
    {
        count ++;
        commands = commands->next;
    }
    return count;
}