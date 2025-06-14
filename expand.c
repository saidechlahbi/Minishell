#include "includes/minishell.h"

char *expand(char *var, t_env *env)
{
    while (env)
    {
        if (!ft_strcmp(var, env->key))
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

char *prep(char *input, t_env *env)
{
    int		in_squote;
	int		in_dquote;
    int		i;
    int		start;
    char *expanded;
    char *value;

    in_squote = 0;
	in_dquote = 0;
    i = 0;
    start = 0;
    expanded = ft_strdup("");
    while(input[i])
    {
		if (input[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
        if(input[i] == '\'' && !in_dquote)
            in_squote = !in_squote;
        if(input[i] == '$' && !in_squote && is_expandable(input[i + 1]))
        {
            expanded = ft_strjoin(expanded, _substr(input, start, i - start));
            i++;
            if (is_expandable(input[i]))
            {
                start = i;
                while(input[i] && is_expandable2(input[i]))
                    i++;
                value = expand(_substr(input, start, i - start), env);
                if (value)
                    expanded = ft_strjoin(expanded, value);
            }
            start = i;
        }
        else
            i++;
    }
    if (i > start)
        expanded = ft_strjoin(expanded, _substr(input, start, i - start));
    return (expanded);
}

void    has_dollar(t_token *tokens, t_env *env)
{
    t_token    *cur;
    t_token    *next;
    char    *expanded;

    cur = tokens;
    while (cur)
    {
        next = cur->next;
        if (ft_strchr(cur->value, '$'))
        {
            expanded = prep(cur->value, env);
            split_n_insert(cur, expanded);
        }
        cur = next;
    }
}
