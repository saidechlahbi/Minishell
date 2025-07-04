#include "../includes/minishell.h"

void remove_quotes(t_token *tokens, char *encapsulizer)
{
    t_token *cur;
    char *new_val;
    int in_squote, in_dquote, encapsuled, i, j;
    
    in_squote = 0;
    in_dquote = 0;
    encapsuled = 0;
    cur = tokens;
    while (cur)
    {
        new_val = ft_calloc(1, ft_strlen(cur->value) + 1);
        i= 0;
        j = 0;
        while (cur && cur->value[i])
        {
            if (!ft_strncmp(&cur->value[i], encapsulizer, 19))
            {
                i+=19;
                encapsuled = !encapsuled;
            }
            else if (cur->value[i] == '\'' && !in_dquote && !encapsuled)
            {
                in_squote = !in_squote;
                i++;
            }
            else if (cur->value[i] == '"' && !in_squote && !encapsuled)
            {
                in_dquote = !in_dquote;
                i++;
            }
            else
                new_val[j++] = cur->value[i++];
        }
        new_val[j] = 0;
        cur->value = new_val;
        cur = cur->next;
    }
}
