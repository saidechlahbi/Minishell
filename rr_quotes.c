#include "includes/minishell.h"

char *remove_quotes(char *str)
{
    int i = 0;
    int j = 0;
    int in_squote = 0;
    int in_dquote = 0;
    char *result;
    
    if (!str)
        return (NULL);
    
    result = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!result)
        return (NULL);
    
    while (str[i])
    {
        if (str[i] == '\'' && !in_dquote)
        {
            in_squote = !in_squote;
            i++;
        }
        else if (str[i] == '"' && !in_squote)
        {
            in_dquote = !in_dquote;
            i++;
        }
        else
        {
            result[j] = str[i];
            i++;
            j++;
        }
    }
    result[j] = 0;
    return (result);
}

void restore_quotes(char *str)
{
    int i = 0;
    
    if (!str)
        return;
    
    while (str[i])
    {
        if (str[i] == 14)
            str[i] = '\'';
        else if (str[i] == 15)
            str[i] = '"';
        i++;
    }
}
