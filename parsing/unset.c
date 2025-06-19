#include "../includes/minishell.h"

void unset(t_env **env, const char *value)
{
    t_env *cur = *env;
    t_env *prev = NULL;

    while (cur)
    {
        if (!strcmp(cur->key, value))
        {
            if (prev == NULL)
                *env = cur->next;
            else
                prev->next = cur->next;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}
