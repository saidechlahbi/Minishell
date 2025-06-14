#include "includes/minishell.h"

void split_n_insert(t_token *cur, char *value)
{
    char **splits;
    t_token *new_node;
    t_token *next;
    int i;

    splits = ft_split(value, ' ');
    cur->value = ft_strdup(splits[0]);
    next = cur->next;
    i = 1;
    while (splits[i])
    {
        new_node = malloc(sizeof(t_token));
        if (!new_node)
            break;
        new_node->value = ft_strdup(splits[i]);
        new_node->next = cur->next;
        cur->next = new_node;
        cur = new_node;
        i++;
    }
}
