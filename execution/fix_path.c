/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:57:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/20 01:33:12 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **env_lst_to_char2(t_env *env, t_garbage **garbage)
{
    t_env *tmp;
    char **envp;
    char *str;
    int count;

    tmp = env;
    count = 0;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    envp = ft_malloc (sizeof(char *) * (count + 1), 1 , garbage);
    count = 0;
    while (env)
    {
        str = ft_strjoin(env->key, "=", garbage);
        envp[count++] = ft_strjoin(str, env->value, garbage);
        env = env->next;
    }
    envp[count] = NULL;
    return envp;
}

static char **get_paths(t_env *env, t_garbage **garbage)
{
    char **paths;
    
    paths = NULL;
    while (env)
    {
        if (ft_strcmp(env->key , "PATH") == 0)
        {
            paths = ft_split(env->value, ':', garbage);
            return paths;
        }
        env = env->next;
    }
    return NULL;
}

int check(char *str)
{
    char *bin;
    int i;

    i = 0;
    bin = "bin";
    while (str[i])
    {
        if (str[i] == bin[i])
        {
            if (ft_strncmp(&str[i], bin, 3) == 1)
                return 1;
        }
        i++;
    }
    return 0;
}

static char *get_right_path(t_env *env, char *cmd, t_garbage **garbage)
{
    char **paths;
    char *cmd_with_path, *str;

    if (check(cmd) == 1)
        if (!access(cmd, X_OK))
            return ft_strdup(cmd, garbage);
    paths = get_paths(env, garbage);
    if (!paths)
        return NULL;
    while (*paths)
    {
        str = ft_strjoin(*paths, "/", garbage);
        cmd_with_path = ft_strjoin(str, cmd, garbage);
        if (access(cmd_with_path, X_OK) == 0)
            return (cmd_with_path);
        paths++;
    }
    return NULL;
}

void fill_by_path(t_cmds *commands, t_env *env, t_garbage **garbage)
{
    char *cmd;

    while (commands)
    {
        if (commands->cmd && commands->type == CMD)
        {
            if (commands->cmd[0][0] == 0)
            {
                commands->executable = 1;
                return ;
            }
            cmd = get_right_path(env, commands->cmd[0], garbage);
            if (cmd)
            {
                commands->cmd[0] = cmd;
                commands->executable = 1;
            }
        }
        commands = commands->next;
    }
}
