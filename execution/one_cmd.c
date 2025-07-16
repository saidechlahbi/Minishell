/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 03:54:14 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/16 04:45:04 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_cmd(t_cmds *commands, char **env, int *pid, t_garbage *garbage)
{
    *pid = fork();
    if (*pid == 0)
    {
        if (redirection(commands) == 0)
            get_out_from_here(garbage, 1);
        if (commands->executable == 0)
        {
            printf("%s: command not found\n", commands->cmd[0]);
            get_out_from_here(garbage, 127);
        }
        redirection(commands);
        if (commands->read_from)
            dup2(commands->read_from, 0);
        if (commands->write_in)
            dup2(commands->write_in, 1);
        execve(commands->cmd[0], commands->cmd, env);
        perror("execve");
        get_out_from_here(garbage, 1);
    }
    return ;
}

int check_is_built_in(char *cmd)
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
            return 1;
        i++;
    }
    return 0;
}

void one_command(t_cmds *commands, char **env, int *exit_status, t_garbage *garbage)
{
    int pid;
    int status;

    // execute_built_in();
    if (check_is_built_in(commands->cmd[0]))
        return ;
    else
    {
        execute_cmd(cmd, env, &pid, garbage);
        waitpid(pid, &status, 0);
    }
}