#include "../includes/minishell.h"

void remove_quotes(t_token *tokens, char *encapsulizer)
{
    t_token *cur;
    char *new_value;
    int i, j;
    int in_squote, in_dquote, expanded;

    cur = tokens;
    while (cur)
    {
        if (cur->value)
        {
            i = 0;
            j = 0;
            in_squote = 0;
            in_dquote = 0;
            expanded = 0;
            new_value = malloc((ft_strlen(cur->value) + 1));
            while (cur->value[i])
            {
                if (encapsulizer && !ft_strncmp(&cur->value[i], encapsulizer, 19))
                {
                    i += 19;
                    expanded = !expanded;
                }
                else if (cur->value[i] == '\'' && (!in_dquote || !expanded))
                {
                    in_squote = !in_squote;
                    i++;
                }
                else if (cur->value[i] == '"' && (!in_squote || !expanded))
                {
                    in_dquote = !in_dquote;
                    i++;
                }
                else
                    new_value[j++] = cur->value[i++];
            }
            new_value[j] = 0;
            cur->value = new_value;
        }
        cur = cur->next;
    }
}
