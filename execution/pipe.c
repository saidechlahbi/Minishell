/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:43:52 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/10 01:11:50 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static void first_pipe(t_cmds *commands, char **env, int *f_pipe, int *pid)
{
    *pid = fork();

    if (*pid == 0)
    {
        if (commands->read_from)
            dup2(commands->read_from, 0);
        if (commands->write_in)
            dup2(commands->write_in, 1);
        else
            dup2(f_pipe[1], 1);
        close(f_pipe[1]);
        close(f_pipe[0]);
        if (!commands->cmd)
            exit(1);
        if (!commands->executable)
        {
            printf("%s: command not found\n", commands->cmd[0]);
            exit(1);
        }
        execve(commands->cmd[0], commands->cmd, env);
        perror("execve");
        exit(1);
    }
    return;
}

static void middle_pipe(t_cmds *commands, char **env, int *f_pipe, int *s_pipe, int *pid)
{
    *pid = fork();
    if (*pid == 0)
    {
        if (commands->read_from)
            dup2(commands->read_from, 0);
        else
            dup2(f_pipe[0], 0);
        if (commands->write_in)
            dup2(commands->write_in, 1);
        else
            dup2(s_pipe[1], 1);
        close(f_pipe[1]);
        close(f_pipe[0]);
        close(s_pipe[1]);
        close(s_pipe[0]);
        if (!commands->cmd)
            exit(1);
        if (!commands->executable)
        {
            printf("%s: command not found\n", commands->cmd[0]);
            exit(1);
        }
        execve(commands->cmd[0], commands->cmd, env);
        perror("execve");
        exit(1);
    }
}

static void last_pipe(t_cmds *commands, char **env, int *f_pipe, int *pid)
{
    *pid = fork();
    if (*pid == 0)
    {
        if (commands->read_from)
            dup2(commands->read_from, 0);
        else
            dup2(f_pipe[0], 0);
        if (commands->write_in)
            dup2(commands->write_in, 1);
        close(f_pipe[1]);
        close(f_pipe[0]);
        if (!commands->cmd)
            exit(1);
        if (!commands->executable)
        {
            printf("%s: command not found\n", commands->cmd[0]);
            exit(1);
        }
        execve(commands->cmd[0], commands->cmd, env);
        perror("execve");
        exit(1);
    }
}

int lst_size(t_cmds *commands)
{
    int count;

    count = 0;
    while (commands)
    {
        count++;
        commands = commands->next;
    }
    return count;
}
void alone_cmd(t_cmds *commands, char **env, int *pid)
{
    *pid = fork();
    if (*pid == 0)
    {
        if (commands->read_from)
            dup2(commands->read_from, 0);
        if (commands->write_in)
            dup2(commands->write_in, 1);
        if (!commands->cmd)
            exit(1);
        if (!commands->executable)
        {
            printf("%s: command not found\n", commands->cmd[0]);
            exit(1);
        }
        execve(commands->cmd[0], commands->cmd, env);
        perror("execve");
        exit(1);
    }
    return ;
}

int wait_commands(int size, int *pids)
{
    int i;
    int status[size];

    i = 0;
    while (i < size)
    {
        waitpid(pids[i], &status[i], 0);
        i++;
    }
    return (WEXITSTATUS(status[size - 1]));
}

void pipes(t_cmds *commands, char **envp, int *last_exit_status)
{
    int f_pipe[2];
    int s_pipe[2];
    int pids[lst_size(commands)];
    int i;

    if (lst_size(commands) == 1)
    {
        alone_cmd(commands, envp, &pids[0]);
        *last_exit_status = wait_commands(lst_size(commands), pids);
        return;
    }
    pipe(f_pipe);
    first_pipe(commands, envp, f_pipe, &pids[0]);
    commands = commands->next;
    i = 1;
    while (commands->next)
    {
        pipe(s_pipe);
        middle_pipe(commands, envp, f_pipe, s_pipe, &pids[i++]);
        close(f_pipe[0]);
        close(f_pipe[1]);
        f_pipe[0] = s_pipe[0];
        f_pipe[1] = s_pipe[1];
        commands = commands->next;
    }
    last_pipe(commands, envp, f_pipe, &pids[i]);
    close(f_pipe[1]);
    close(f_pipe[0]);
    *last_exit_status = wait_commands(lst_size(commands), pids);
    return;
}
