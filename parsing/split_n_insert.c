/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_n_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:35 by schahir           #+#    #+#             */
/*   Updated: 2025/07/13 11:16:29 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_tok(char *input, char *encapsulizer)
{
    int i = 0;
    int start = 0;
    int count = 0;
    int in_squote= 0;
    int in_dquote = 0;
    int ignore = 0;

    while(input[i])
    {
        if (!ft_strncmp(&input[i], encapsulizer, 19))
        {
            i+=19;
            ignore = !ignore;
        }
        else if(input[i] == '\'' && (!in_dquote && !ignore))
        {
            in_squote = !in_squote;
            i++;
        }
        else if(input[i] == '"' && (!in_squote && !ignore))
        {
            in_dquote = !in_dquote;
            i++;
        }
        else if(!in_squote && !in_dquote && ft_isspace(input[i]))
        {
            if (i > start)
                count++;
            i++;
            while (ft_isspace(input[i]))
                i++;
        }
        else
            i++;
    }
    if (i > start)
        count++;
    return (count);
}

char **str_tok(char *input, char *encapsulizer, t_garbage *garbage)
{
    int        i;
    int        start = 0;
    int        in_squote = 0;
    int        in_dquote = 0;
    char       **tokens = NULL;
    int        j = 0;
    int        ignore = 0;

    i = 0;
    tokens = ft_malloc(sizeof(char *) , (count_tok(input, encapsulizer) + 1), garbage);
    while(input[i])
    {
        if (!ft_strncmp(&input[i], encapsulizer, 19))
        {
            i+=19;
            ignore = !ignore;
        }
        else if(input[i] == '\'' && (!in_dquote && !ignore))
        {
            in_squote = !in_squote;
            i++;
        }
        else if(input[i] == '"' && (!in_squote && !ignore))
        {
            in_dquote = !in_dquote;
            i++;
        }
        else if(!in_squote && !in_dquote && ft_isspace(input[i]))
        {
            if (i > start)
                tokens[j++] = _substr(input, start, i - start, garbage);
            i++;
            while (ft_isspace(input[i]))
                i++;
            start = i;
        }
        else
            i++;
    }
    if (i > start)
        tokens[j++] = _substr(input, start, i - start, garbage);
    
    tokens[j] = NULL;
    
    return (tokens);
}

void split_n_insert(t_token *cur, char *enapsulizer, t_garbage *garbage)
{
    char **splits;
    t_token *new;
    int i;

    if (!cur->value[0])
        return ;
    splits = str_tok(cur->value, enapsulizer, garbage);
    cur->value = ft_strdup(splits[0], garbage);
    // cur->type = AMBIGIUOS;
    i = 1;
    while (splits[i])
    {
        new = ft_malloc(sizeof(t_token), 1, garbage);
        new->value = ft_strdup(splits[i], garbage);
        new->type = AMBIGIUOS;
        new->next = cur->next;
        cur->next = new;
        cur = new;
        i++;
    }
}
