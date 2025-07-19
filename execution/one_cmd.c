/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 03:54:14 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/19 21:15:56 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void execute_cmd(t_cmds *commands, int *pid, t_garbage *garbage)
{
    *pid = fork();
    if (*pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (open_files(commands) == 0)
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
        execve(commands->cmd[0], commands->cmd, commands->envp);
        perror("execve");
        close_all_fds_fstat(0);
        get_out_from_here(garbage, 1);
    }
    else
        g_global_signal = -1;
    return ;
}

void one_command(t_cmds *commands, t_env **env, int *exit_status, t_garbage **garbage)
{
    int pid;
    int status;

    if (!commands->cmd)
    {
        if (open_files(commands) == 0)
            *exit_status = 1;
        return ;
    }
    if (commands->type == BUILTIN)
        execute_built_in(commands->cmd, env, garbage);
    else
    {
        execute_cmd(commands, &pid, *garbage);
        waitpid(pid, &status, 0);
        *exit_status = WEXITSTATUS(status);
    }
}
