#include "../includes/minishell.h"

void remove_quotes(t_token *tokens)
{
    t_token *cur;
    char *new_value;
    int i, j;
    int in_squote, in_dquote;
    
    if (!tokens)
        return;
    
    cur = tokens;
    while (cur)
    {
        if (cur->value)
        {
            i = 0;
            j = 0;
            in_squote = 0;
            in_dquote = 0;
            new_value = malloc(sizeof(char) * (ft_strlen(cur->value) + 1));
            if (!new_value)
            {
                cur = cur->next;
                continue;
            }
            while (cur->value[i])
            {
                if (cur->value[i] == '\'' && !in_dquote)
                {
                    in_squote = !in_squote;
                    i++;
                }
                else if (cur->value[i] == '"' && !in_squote)
                {
                    in_dquote = !in_dquote;
                    i++;
                }
                else
                {
                    new_value[j] = cur->value[i];
                    i++;
                    j++;
                }
            }
            new_value[j] = 0;
            cur->value = new_value;
        }
        cur = cur->next;
    }
}

void restore_quotes(t_token *tokens)
{
    t_token *cur;
    int i;
    
    if (!tokens)
        return;
    
    cur = tokens;
    while (cur)
    {
        if (cur->value)
        {
            i = 0;
            while (cur->value[i])
            {
                if (cur->value[i] == 14)
                    i++;
                i++;
            }
        }
        cur = cur->next;
    }
}
