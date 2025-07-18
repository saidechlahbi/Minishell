/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:43:52 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/18 00:48:54 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void first_pipe(t_cmds *command, char **env, int *f_pipe, t_garbage *garbage)
{
    command->pid = fork();
    if(command->pid == -1)
    {
        perror("fork");
        get_out_from_here(garbage, 1);
    }
    if (command->pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        open_and_redirec(command, garbage);
        if (command->read_from)
            dup2(command->read_from, 0);
        if (command->write_in)
            dup2(command->write_in, 1);
        else
            dup2(f_pipe[1], 1);
        close(f_pipe[1]);
        close(f_pipe[0]);
        execution_cmd(command, env, garbage);
    }
    else
        g_global_signal = -1;
    return;
}

static void middle_pipe(t_cmds *command, char **env, int *f_pipe,  t_garbage *garbage)
{
    command->pid = fork();
    if(command->pid == -1)
    {
        perror("fork");
        get_out_from_here(garbage, 1);
    }
    if (command->pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        open_and_redirec(command, garbage);
        if (command->read_from)
            dup2(command->read_from, 0);
        else
            dup2(f_pipe[0], 0);
        if (command->write_in)
            dup2(command->write_in, 1);
        else
            dup2(f_pipe[1], 1);
        close(f_pipe[1]);
        close(f_pipe[0]);
        execution_cmd(command, env, garbage);
    }
    else
        g_global_signal = -1;
}

static void last_pipe(t_cmds *command, char **env, int *f_pipe, t_garbage *garbage)
{
    command->pid = fork();
    if(command->pid == -1)
    {
        perror("fork");
        get_out_from_here(garbage, 1);
    }
    if (command->pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        open_and_redirec(command, garbage);
        if (command->read_from)
            dup2(command->read_from, 0);
        else
            dup2(f_pipe[0], 0);
        if (command->write_in)
            dup2(command->write_in, 1);
        close(f_pipe[1]);
        close(f_pipe[0]);
        execution_cmd(command, env, garbage);
    }
    else
        g_global_signal = -1;
}

static int wait_commands(int size, t_cmds * cmd)
{
    int i;
    int status[size];

    i = 0;
    while (cmd)
    {
        waitpid(cmd->pid, &status[i], 0);
        cmd = cmd->next;
    }
    if (WIFSIGNALED(status[size - 1]))
        return (WTERMSIG(status[size - 1]) + 128);
    if (WIFEXITED(status[size - 1]))
        return (WEXITSTATUS(status[size - 1]));
    return (WEXITSTATUS(status[size - 1]));
}

void pipes(t_cmds *commands, char **envp, int *exit_status, t_garbage *garbage)
{
    int f_pipe[2];
    int s_pipe[2];
    t_cmds *tmp;

    tmp = commands;
    pipe(f_pipe);
    first_pipe(tmp, envp, f_pipe, garbage);
    tmp = tmp->next;
    while (tmp->next)
    {
        close(f_pipe[1]);
        pipe(s_pipe);
        f_pipe[1] = s_pipe[1];
        middle_pipe(tmp, envp, f_pipe, garbage);
        close(f_pipe[0]);
        f_pipe[0] = s_pipe[0];
        f_pipe[1] = s_pipe[1];
        tmp = tmp->next;
    }
    last_pipe(tmp, envp, f_pipe, garbage);
    close(f_pipe[1]);
    close(f_pipe[0]);
    *exit_status = wait_commands(ft_size(commands),commands);
    return;
}
