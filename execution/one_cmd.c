/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 03:54:14 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/22 19:08:33 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_if_is_it_dir(char *cmd)
{
    struct stat stat_dir;

    if (ft_strchr(cmd, '/'))
    {
        if (!stat(cmd, &stat_dir))
            if (S_ISDIR(stat_dir.st_mode))
            {
                ft_putstr_fd("bash: ", 2);
                ft_putstr_fd(cmd, 2);
                ft_putstr_fd(": Is a directory\n", 2);
                return 1;
            }
    }
    return 0;
}

static int execute_cmd(t_cmds *commands, int *pid, t_garbage *garbage)
{
    *pid = fork();
    if (*pid == -1)
    {
        perror("fork failed\n");
        return 1;
    }
    if (*pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if(check_if_is_it_dir(commands->cmd[0]))
            get_out_from_here(garbage, 126);
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
    return 0;
}

static void execute_cmd_built_in(t_cmds *commands, t_env **env, int *exit_status, t_garbage **garbage)
{
    int std_in;
    int std_out;

    std_in = dup(0);
    std_out = dup(1);
    if (open_files(commands) == 0 || std_in == -1 || std_out == -1)
    {
        *exit_status = 1;
        return;
    }
    redirection(commands);
    if (commands->read_from)
        dup2(commands->read_from, 0);
    if (commands->write_in)
        dup2(commands->write_in, 1);
    execute_built_in(commands->cmd, env, garbage);
    close(0);
    close(1);
    dup(std_in);
    dup(std_out);
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
        execute_cmd_built_in(commands, env, exit_status, garbage);
    else
    {
        if (execute_cmd(commands, &pid, *garbage))
        {
            *exit_status = 1;
            return ;
        }
        waitpid(pid, &status, 0);
        *exit_status = WEXITSTATUS(status);
    }
}
