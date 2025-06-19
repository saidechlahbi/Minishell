/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:43:52 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/19 18:40:09 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char* get_right_path(t_env *env, char *cmd)
{
    char **paths;

    paths = NULL;
    if (!access(cmd, X_OK))
        return cmd;
    while (env)
    {
        if (ft_strcmp(env->key , "PATH") == 0)
        {
            paths = ft_split(env->value, ':');
            break;
        }
        env = env->next;
    }
    char *str;
    if (paths)
    {
        while (*(paths++))
        {
            str = ft_strjoin(*paths, cmd);
            if (!access(str, X_OK))
                return str;
            free(str);
        }
    }
    return NULL;
}

void first_pipe(t_fds fds, )
{
    char *str = "ls"



    char *str = "/bin/ls";
    char **ss = {"ls", "-la", NULL};
    execve(str, ss, NULL)
}
void middle_pipe(t_fds *fds)
{
    
}
void last_pipe(t_fds fds)
{
    
}

void pipes(t_token *token, t_env *env)
{
    t_fds fds;
    
    int i = 2;
    char *cmd = get_right_path(env, );
    first_pipe()
    while (i < 2)
    {
        
    }
    last_pipe()
    
}