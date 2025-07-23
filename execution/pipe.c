/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:43:52 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/22 19:12:45 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int first_pipe(t_cmds *command, t_env **env, int *f_pipe, t_garbage **garbage)
{
    command->pid = fork();
    if(command->pid == -1)
    {
        perror("fork failed\n");
        return 1;
    }
    if (command->pid == 0)
    {
        if(check_if_is_it_dir(command->cmd[0]))
            get_out_from_here(*garbage, 126);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        open_and_redirec(command, *garbage);
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
    return 0;
}

static int middle_pipe(t_cmds *command, t_env **env, int *f_pipe,  t_garbage **garbage)
{
    command->pid = fork();
    if(command->pid == -1)
    {
        perror("fork failed\n");
        return 1;
    }
    if (command->pid == 0)
    {
        if(check_if_is_it_dir(command->cmd[0]))
            get_out_from_here(*garbage, 126);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        open_and_redirec(command, *garbage);
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
    return 0;
}

static int last_pipe(t_cmds *command, t_env **env, int *f_pipe, t_garbage **garbage)
{
    command->pid = fork();
    if(command->pid == -1)
    {
        perror("fork failed\n");
        return 1;
    }
    if (command->pid == 0)
    {
        if(check_if_is_it_dir(command->cmd[0]))
            get_out_from_here(*garbage, 126);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        open_and_redirec(command, *garbage);
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
    return 0;
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
        i++;
    }
    if (WIFSIGNALED(status[size - 1]))
        return (WTERMSIG(status[size - 1]) + 128);
    if (WIFEXITED(status[size - 1]))
        return (WEXITSTATUS(status[size - 1]));
    return (WEXITSTATUS(status[size - 1]));
}

void pipes(t_cmds *commands, int *exit_status, t_env **env, t_garbage **garbage)
{
    int f_pipe[2];
    int s_pipe[2];
    t_cmds *tmp;

    tmp = commands;
    pipe(f_pipe);
    if (first_pipe(tmp, env, f_pipe, garbage))
    {
        *exit_status = 1;
        return ;
    }
    tmp = tmp->next;
    while (tmp->next)
    {
        close(f_pipe[1]);
        pipe(s_pipe);
        f_pipe[1] = s_pipe[1];
        if (middle_pipe(tmp, env, f_pipe, garbage))
        {
            *exit_status = 1;
            return ;
        }
        close(f_pipe[0]);
        f_pipe[0] = s_pipe[0];
        f_pipe[1] = s_pipe[1];
        tmp = tmp->next;
    }
    if (last_pipe(tmp, env, f_pipe, garbage))
    {
        *exit_status = 1;
        return ;
    }
    close(f_pipe[1]);
    close(f_pipe[0]);
    *exit_status = wait_commands(ft_size(commands),commands);
    return;
}
