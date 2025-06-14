#include "includes/minishell.h"

char **str_tok(char *input)
{
    int		i = 0;
	int		start = 0;
	int		in_squote = 0;
	int		in_dquote = 0;
    char    **tokens = NULL;
    int     j = 0;

    tokens = malloc(999);
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
        else if(!in_squote && !in_dquote &&ft_isspace(input[i]))
        {
            if (i > start)
                tokens[j++] = _substr(input, start, i -start);
            i++;
            while (ft_isspace(input[i]))
                i++;
            start = i;
        }
        else
            i++;
    }
     if (i > start)
        tokens[i] = _substr(input, start, i - start);
     return (tokens);
}

void split_n_insert(t_token *cur, char *value)
{
    char **splits;
    t_token *new;
    t_token *next;
    int i;

//     i = 0;
//     int in_dquote = 0;
//    // int in_squote = 0;

//      while (value[i])
//     {
//         if (value[i] == '"')
//             in_dquote = !in_dquote;
//         if (value[i] == ' ' && !in_dquote)
//             break;
//         i++;
//     }
//     if (in_dquote || !value[i])
//         return;

    splits = str_tok(value);
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
