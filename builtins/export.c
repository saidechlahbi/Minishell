/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:01 by schahir           #+#    #+#             */
/*   Updated: 2025/07/12 19:03:24 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *sort_export(t_env *copy)
{
    int sorted;
    t_env *tmp;
    char *kc;
    char *vc;

	sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        tmp = copy;
        while (tmp->next)
        {
            if (ft_strcmp(tmp->key, tmp->next->key) > 0)
            {
                kc = tmp->key;
                tmp->key = tmp->next->key;
                tmp->next->key = kc;
                vc = tmp->value;
                tmp->value = tmp->next->value;
                tmp->next->value = vc;
                sorted = 0;
            }
            tmp = tmp->next;
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
