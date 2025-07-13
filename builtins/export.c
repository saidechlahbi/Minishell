/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:01 by schahir           #+#    #+#             */
/*   Updated: 2025/07/13 12:31:35 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *sort_export(t_env *copy)
{
    int sorted;
    char *kc;
    char *vc;

	sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        while (copy->next)
        {
            if (ft_strcmp(copy->key, copy->next->key) > 0)
            {
                kc = copy->key;
                copy->key = copy->next->key;
                copy->next->key = kc;
                vc = copy->value;
                copy->value = copy->next->value;
                copy->next->value = vc;
                sorted = 0;
            }
            copy = copy->next;
        }
    }
    return (copy);
}

void print_export(t_env *env)
{
    t_env *copy = env;
    sort_export(copy);
	int i;

    while (copy)
    {
        printf("declare -x %s", copy->key);
        if (copy->value)
        {
            printf("=\"");
			i = 0;
            while (copy->value[i])
            {
                if (copy->value[i] == '"')
                    printf("\\\"");
                else if (copy->value[i] == '$')
                    printf("\\$");
                else
                    printf("%c", copy->value[i]);
				i++;
            }
            printf("\"");
        }
        printf("\n");
        copy = copy->next;
    }
}

t_env *find_key(t_env *env, char *key)
{
    while (env)
    {
        if (!ft_strcmp(env->key, key))
            return env;
        env = env->next;
    }
    return (NULL);
}

void export_variable( t_env **env, char *arg)
{
    t_garbage *garbage;
    char    *equal;
    char    *newk;
    char    *newv;
    int     i;

    if (!arg || !arg[0])
        return;
    i = 0;
    if (is_expandable(arg[i]))
    {
        while (arg[i])
        {
            if (is_expandable2(arg[i]))
                i++;
        }
    }
    if (arg[i])
    {
        if (arg[i] == '+')
            i++;
        if(arg[i] != '=')
            return ;
    }
    equal = ft_strchr(arg, '=');
    if (!equal)
    {
        newk = ft_strdup(arg, garbage);
        newv = NULL;
    }
    else if (arg[*(equal - 1)] == '+')
    {
        newk = _substr(arg, 0, equal - 1 - arg, garbage);
        if (!find_key(env, newk))
            newv = ft_strdup(equal + 1, garbage);
        else
            newv = ft_strjoin(*env->value, newv, garbage);
    }
    else
    {   
        newk = _substr(arg, 0, equal - arg, garbage);
        newv = ft_strdup(equal + 1, garbage);
    }
    if (!find_key(env, newk))
        add_var(env, newk, newv, garbage);
    else
        *env->value = newv;
}


void export(t_env **env, char **args)
{
    int i;
    
    if (!args || !args[1])
    {
        print_export(*env);
        return;
    }
    i = 1;
    while (args[i])
    {
        export_variable(env, args[i]);
        i++;
    }
}
