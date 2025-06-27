#include "../includes/minishell.h"

char *expand(char *var, t_env *env, char *encapsulizer)
{
    char *input;
    int i;
    int start;

    i = 0;
    start = 0;
    while (env)
    {
        if (!ft_strcmp(var, env->key))
        {
            input = ft_strdup(encapsulizer);
            input = ft_strjoin(input, env->value);
            input = ft_strjoin(input, encapsulizer);
            return (input);
        }
        env = env->next;
    }
    return (NULL);
}

char *prep(char *input, t_env *env, char *encapsulizer)
{
    int in_squote;
    int in_dquote;
    int i;
    int start;
    char *expanded;
    char *value;

    in_squote = 0;
    in_dquote = 0;
    i = 0;
    start = 0;
    expanded = ft_strdup("");
    while (input[i])
    {
        if (input[i] == '"' && !in_squote)
            in_dquote = !in_dquote;
        if (input[i] == '\'' && !in_dquote)
            in_squote = !in_squote;
        if (input[i] == '$' && !in_squote && is_expandable(input[i + 1]))
        {
            expanded = ft_strjoin(expanded, _substr(input, start, i - start));
            i++;
            if (is_expandable(input[i]))
            {
                start = i;
                while (input[i] && is_expandable2(input[i]))
                    i++;
                value = expand(_substr(input, start, i - start), env, encapsulizer);
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
    // printf("here1 %s\n", expanded);
    return (expanded);
}

void has_dollar(t_token *tokens, t_env *env)
{
    t_token *cur;
    t_token *next;
    char *expanded;
    char *encapsulizer;

    cur = tokens;
    encapsulizer = randomize();
    while (cur)
    {
        next = cur->next;
        if (ft_strchr(cur->value, '$'))
        {
            expanded = prep(cur->value, env, encapsulizer);
            cur->value = expanded;
            split_n_insert(cur);
        }
        cur = next;
    }
    remove_quotes(tokens, encapsulizer);
}
