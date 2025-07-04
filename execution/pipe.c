/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:43:52 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/04 12:00:52 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void read_from(t_cmds *commands)
{

    t_redirection *tmp;

    commands->read_from = 0;
    commands->write_in = 0;
    tmp = commands->redirection;
    while (tmp)
    {
        if (tmp->type == IN_FILE)
            commands->read_from = tmp->fd;
        else if (tmp->type == OUT_FILE || tmp->type == APP_FILE)
            commands->write_in = tmp->fd;
        tmp = tmp->next;
    }
    if (commands->read_from)
        dup2(commands->read_from, 0);   
    if (commands->write_in)
        dup2(commands->write_in, 1);
    return;
}

static void first_pipe(t_cmds *commands, char **env, int *f_pipe)
{
    int pid = fork();
    if (pid == 0)
    {
        if (commands->redirection)
            read_from(commands);
        if (commands->write_in == 0)
            dup2(f_pipe[1], 1);
        close(f_pipe[1]);
        close(f_pipe[0]);

        execve(commands->cmd[0], commands->cmd, env);
        exit(1);
    }
    return;
}

static void middle_pipe(t_cmds *commands, char **env, int *f_pipe, int *s_pipe)
{
    int pid = fork();
    if (pid == 0)
    {
        if (commands->redirection)
            read_from(commands);
        if (commands->read_from == 0)
            dup2(f_pipe[0], 0);
        if (commands->write_in == 0)
            dup2(s_pipe[1], 1);
        close(f_pipe[1]);
        close(f_pipe[0]);
        close(s_pipe[1]);
        close(s_pipe[0]);
        execve(commands->cmd[0], commands->cmd, env);
        exit(1);
    }
}

static void last_pipe(t_cmds *commands, char **env, int *f_pipe)
{
    int pid = fork();
    if (pid == 0)
    {
        if (commands->redirection)
            read_from(commands);
        if (commands->read_from == 0)
            dup2(f_pipe[0], 0);
        close(f_pipe[1]);
        close(f_pipe[0]);

        execve(commands->cmd[0], commands->cmd, env);
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
void alone_cmd(t_cmds *commands, char **env)
{
    int pid = fork();
    if (pid == 0)
    {
        if (commands->redirection)
            read_from(commands);
        execve(commands->cmd[0], commands->cmd, env);
        exit(1);
    }
    return ;
}

void pipes(t_cmds *commands, t_env *env)
{
    int f_pipe[2];
    int s_pipe[2];
    char **envp;

    open_files(commands);
    fill_by_path(commands, env);
    envp = env_lst_to_char2(env);
    if (lst_size(commands) == 1)
    {
        alone_cmd(commands, envp);
        wait(NULL);
        return;
    }
    pipe(f_pipe);
    first_pipe(commands, envp, f_pipe);
    commands = commands->next;
    while (commands->next)
    {
        pipe(s_pipe);
        middle_pipe(commands, envp, f_pipe, s_pipe);
        close(f_pipe[0]);
        close(f_pipe[1]);
        f_pipe[0] = s_pipe[0];
        f_pipe[1] = s_pipe[1];
        commands = commands->next;
    }
    last_pipe(commands, envp, f_pipe);
    close(f_pipe[1]);
    close(f_pipe[0]);
    wait(NULL);
    wait(NULL);
    return;
}
