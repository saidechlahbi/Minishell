#include "includes/minishell.h"

void split_n_insert(t_token *current, char *value)
{
    char **splits;
    t_token *new_node;
    t_token *next_backup;
    int i;

    splits = ft_split(value, ' ');
    if (!splits || !splits[0])
    {
        free(current->value);
        current->value = ft_strdup(value);
        return;
    }

    free(current->value);
    current->value = ft_strdup(splits[0]);
    
    next_backup = current->next;
    

    i = 1;
    while (splits[i])
    {
        new_node = malloc(sizeof(t_token));
        if (!new_node)
            break;
        new_node->value = ft_strdup(splits[i]);
        new_node->next = current->next;
        current->next = new_node;
        current = new_node;
        i++;
    }
}