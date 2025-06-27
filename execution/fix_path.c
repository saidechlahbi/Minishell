/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:57:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/27 15:52:27 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **env_lst_to_char2(t_env *env)
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
    envp = malloc (sizeof(char *) * (count + 1));
    count = 0;
    while (env)
    {
        str = ft_strjoin(env->key, "=");
        envp[count++] = ft_strjoin(str, env->value);
        free(str);
        env = env->next;
    }
    envp[count] = NULL;
    return envp;
}

static char **get_paths(t_env *env)
{
    char **paths;
    
    paths = NULL;
    while (env)
    {
        if (ft_strcmp(env->key , "PATH") == 0)
        {
            paths = ft_split(env->value, ':');
            if (!paths)
                return NULL;
            return paths;
        }
        env = env->next;
    }
    return NULL;
}

static char *get_right_path(t_env *env, char *cmd)
{
    char **paths;
    char *cmd_with_path, *str;

    if (!access(cmd, X_OK))
        return ft_strdup(cmd);
    paths = get_paths(env);
    if (!paths)
        return NULL;
    while (*paths)
    {
        str = ft_strjoin(*paths, "/");
        cmd_with_path = ft_strjoin(str, cmd);
        free(str);
        if (access(cmd_with_path, X_OK) == 0)
            return (cmd_with_path);
        free(cmd_with_path);
        paths++;
    }
    return NULL;
}

void fill_by_path(t_cmds *commands, t_env *env)
{
    char *cmd;

    while (commands)
    {
        if (commands->cmd && commands->type != BUILTIN)
        {
            cmd = get_right_path(env, commands->cmd[0]);
            if (cmd)
            {
                free(commands->cmd[0]);
                commands->cmd[0] = cmd;
            }
        }
        commands = commands->next;
    }
}