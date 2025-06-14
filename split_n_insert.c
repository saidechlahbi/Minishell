#include "includes/minishell.h"

void split_n_insert(t_token *cur, char *value)
{
    char **splits;
    t_token *new;
    t_token *next;
    int i = 0;
    int in_quote = 0;

     while (value[i])
    {
        if (value[i] == '"')
            in_quote = !in_quote;
        if (value[i] == ' ' && !in_quote)
            break;
        i++;
    }
    if (in_quote || !value[i])
        return;

    splits = ft_split(value, ' ');
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
// a= 1   2   3
// hhhhh$a"said"