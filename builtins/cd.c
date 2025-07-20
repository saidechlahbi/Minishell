/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:31:55 by schahir           #+#    #+#             */
/*   Updated: 2025/07/20 20:57:40 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void set_oldpwd(t_env **env, char *pwd, char *old, t_garbage **garbage)
{
    char *tmp;

        tmp = ft_strjoin("PWD=", pwd, garbage);
        export_variable(env, tmp, garbage);
        tmp = ft_strjoin("OLDPWD=", old, garbage);
        export_variable(env, tmp, garbage);
}

int ft_cd(char **args, t_env **env, t_garbage **garbage)
{
    char    *pwd;
    char    *old;
    char    *target;
    int        res;

    old = getcwd(NULL, 0);
    if (!args[1])
    {
        target = exdoc("HOME", *env);
        if (!target)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            if (old)
                free(old);
            return (1);
        }
        res = chdir(target);
    }
    else
        res = chdir(args[1]);
    if (res)
    {
        perror("cd");
        if (old)
            free(old);
        return (1);
    }
    pwd = getcwd(NULL, 0);
    set_oldpwd(env, pwd, old, garbage);
    if (pwd)
        free(pwd);
    if (old)
        free(old);
    return (0);
}
