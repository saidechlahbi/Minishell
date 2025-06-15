#include "includes/minishell.h"

int count_tok(char *input)
{
    int i = 0;
    int start = 0;
    int count = 0;
    int in_squote= 0;
    int in_dquote = 0;

    while(input[i])
    {
        if(input[i] == '\'' && !in_dquote)
        {
            in_squote = !in_squote;
            i++;
        }
        else if(input[i] == '"' && !in_squote)
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

char **str_tok(char *input)
{
    int        i = 0;
    int        start = 0;
    int        in_squote = 0;
    int        in_dquote = 0;
    char    **tokens = NULL;
    int     j = 0;

    while(input[i])
    {
        if(input[i] == '\'')
            input[i] = 14;
        else if(input[i] == '"')
            input[i] = 15;
        i++;
    }
    i = 0;
    tokens = malloc(sizeof(char *) * (count_tok(input) + 1));
    while(input[i])
    {
        if(input[i] == 14 && !in_dquote)
        {
            in_squote = !in_squote;
            i++;
        }
        else if(input[i] == 15 && !in_squote)
        {
            in_dquote = !in_dquote;
            i++;
        }
        else if(!in_squote && !in_dquote && ft_isspace(input[i]))
        {
            if (i > start)
                tokens[j++] = _substr(input, start, i - start);
            i++;
            while (ft_isspace(input[i]))
                i++;
            start = i;
        }
        else
            i++;
    }
    if (i > start)
        tokens[j++] = _substr(input, start, i - start);
    
    tokens[j] = NULL;
    
    return (tokens);
}

void split_n_insert(t_token *cur)
{
    char **splits;
    t_token *new;
    t_token *next;
    int i;

    if (!cur->value[0])
        return ;
    splits = str_tok(cur->value);
    cur->value = ft_strdup(splits[0]);
    next = cur->next;
    i = 1;
    while (splits[i])
    {
        new = malloc(sizeof(t_token));
        if (!new)
            break;
        new->value = ft_strdup(splits[i]);
        new->next = cur->next;
        cur->next = new;
        cur = new;
        i++;
    }
}
