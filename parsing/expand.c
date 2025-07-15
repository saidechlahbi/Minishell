/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:25 by schahir           #+#    #+#             */
/*   Updated: 2025/07/15 11:40:11 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *expand(char *var, t_env *env, char *encapsulizer, t_garbage *garbage)
{
    char *input;

    while (env)
    {
        if (!ft_strcmp(var, env->key))
        {
            input = ft_strdup(encapsulizer, garbage);
            input = ft_strjoin(input, env->value, garbage);
            input = ft_strjoin(input, encapsulizer, garbage);
            return (input);
        }
        env = env->next;
    }
    return (NULL);
}

char    *exdoc(char *var, t_env *env)
{
    while (env)
    {
        if (!ft_strcmp(var, env->key))
            return env->value;
        env = env->next;
    }
    return (NULL);
}

char *prep(char *input, t_env *env, char *encapsulizer, t_garbage *garbage)
{
    int in_squote;
    int in_dquote;
    int i;
    int start;
    char *expanded;
    char *value;

    in_squote = 0;
    in_dquote = 0;
    i = 0;
    start = 0;
    expanded = ft_strdup("", garbage);
    while (input[i])
    {
        if (input[i] == '"' && !in_squote)
            in_dquote = !in_dquote;
        if (input[i] == '\'' && !in_dquote)
            in_squote = !in_squote;
        if (input[i] == '$' && !in_squote && is_expandable(input[i + 1]))
        {
            expanded = ft_strjoin(expanded, _substr(input, start, i - start, garbage), garbage);
            i++;
            if (is_expandable(input[i]))
            {
                start = i;
                while (input[i] && is_expandable2(input[i]))
                    i++;
                value = expand(_substr(input, start, i - start, garbage), env, encapsulizer, garbage);
                if (value)
                    expanded = ft_strjoin(expanded, value, garbage);
            }
            start = i;
        }
        else
            i++;
    }
    if (i > start)
        expanded = ft_strjoin(expanded, _substr(input, start, i - start, garbage), garbage);
    return (expanded);
}

void has_dollar(t_token *tokens, t_env *env, t_garbage *garbage)
{
    t_token *cur;
    t_token *next;
    char *expanded;
    char *encapsulizer;

    cur = tokens;
    encapsulizer = randomize(garbage);
    while (cur)
    {
        next = cur->next;
        if (ft_strchr(cur->value, '$'))
        {
            expanded = prep(cur->value, env, encapsulizer, garbage);
            cur->value = expanded;
            split_n_insert(cur, encapsulizer, garbage);
        }
        cur = next;
    }
    remove_quotes(tokens, encapsulizer, garbage);
}
