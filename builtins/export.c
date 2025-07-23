/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:01 by schahir           #+#    #+#             */
/*   Updated: 2025/07/23 11:42:20 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *create_copy(t_env *env, t_garbage **garbage)
{
    t_env *new_node;
    t_env *head;
    t_env *tail;

    head = NULL;
    tail = NULL;
    while (env)
    {
        new_node = ft_malloc(sizeof(t_env), 1, garbage);
        new_node->key = ft_malloc(strlen(env->key) + 1, 1, garbage);
        ft_strncpy(new_node->key, env->key, ft_strlen(env->key));
        new_node->key[ft_strlen(env->key)] = '\0';
        if (env->value)
        {
            new_node->value = ft_malloc(strlen(env->value) + 1, 1, garbage);
            ft_strncpy(new_node->value, env->value, ft_strlen(env->value));
            new_node->value[ft_strlen(env->value)] = '\0';
        }
        else
            new_node->value = NULL;
        new_node->next = NULL;
        if (!head)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }
        env = env->next;
    }
    return (head);
}

t_env *sort_export(t_env *head)
{
    int sorted;
    t_env *current;
    char *kc;
    char *vc;

    if (!head)
        return (NULL);
    
    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        current = head;
        while (current && current->next)
        {
            if (ft_strcmp(current->key, current->next->key) > 0)
            {
                kc = current->key;
                current->key = current->next->key;
                current->next->key = kc;
                vc = current->value;
                current->value = current->next->value;
                current->next->value = vc;
                sorted = 0;
            }
            current = current->next;
        }
    }
    return (head);
}

void print_export(t_env *env, t_garbage **garbage)
{
    t_env *copy;
    int i;

    copy = create_copy(env, garbage);
    copy = sort_export(copy);
    while (copy)
    {
        printf("declare -x %s", copy->key);
        if (copy->value)
        {
            printf("=\"");
            i = 0;
            while (copy->value[i])
            {
                printf("%c", copy->value[i]);
                i++;
            }
            printf("\"");
        }
        printf("\n");
        copy = copy->next;
    }
}

t_env	*find_key(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void save_data(t_garbage *garbage)
{
    if (!garbage)
        return ;
    while (garbage->next)
        garbage = garbage->next;
    if (garbage)
        garbage->var = 1;
}

void	export_variable(t_env **env, char *arg, t_garbage **garbage)
{
	char		*equal;
	char		*newk;
	char		*newv;
	t_env		*existing;
	int			i;

	i = 0;
	if (is_expandable(arg[i]))
		while (arg[i] && is_expandable2(arg[i]))
			i++;
	if (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			i += 2;
		else if (arg[i] == '=')
			i++;
		else
		{
            perror("export");
            return ;
        }
	}
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		newk = ft_strdup(arg, garbage);
        save_data(*garbage);
		newv = NULL;
	}
	else if (equal > arg && *(equal - 1) == '+')
	{
		newk = _substr(arg, 0, equal - 1 - arg, garbage);
        save_data(*garbage);
		existing = find_key(*env, newk);
		if (!existing || !existing->value)
			newv = ft_strdup(equal + 1, garbage);
		else
			newv = ft_strjoin(existing->value, equal + 1, garbage);
        save_data(*garbage);
	}
	else
	{
		newk = _substr(arg, 0, equal - arg, garbage);
        save_data(*garbage);
		newv = ft_strdup(equal + 1, garbage);
        save_data(*garbage);
	}
	existing = find_key(*env, newk);
	if (!existing)
		add_var(env, newk, newv, garbage);
	else if (existing && equal)
		existing->value = newv;
}

void	export(t_env **env, char **args, t_garbage **garbage)
{
	int	i;

	if (!args[1])
	{
		print_export(*env, garbage);
		return ;
	}
	i = 1;
	while (args[i])
	{
		export_variable(env, args[i], garbage);
		i++;
	}
}
