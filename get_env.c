#include "includes/minishell.h"

void    add_var(t_env **head, char *key, char *value)
{
    t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env *get_env(char **envp)
{
    t_env *vars = NULL;
    int     i = 0;
    char    *key;
    char    *value;
    char    *equal;

    while (envp[i])
    {
        equal = ft_strchr(envp[i], '=');
        if (equal)
        {
            key = _substr(envp[i], 0, equal - envp[i]);
            value = ft_strdup(equal + 1);
            add_var(&vars, key, value);
        }
        i++;
    }
    return vars;
}

void print_env(t_env *env)
{
    while (env)
    {
        printf("%s = %s\n", env->key, env->value);
        env = env->next;
    }
}

//exported
void new_var(t_token *node, t_env **env_list)
{
    char    *equal;
    char    *key;
    char    *value;
    int     i;

    if (!node || !node->value)
        return;
    i = 0;
    if (is_expandable(node->value));
    while (node->value[i])
    {
        if (is_expandable2(node->value[i]))
            i++;
    }
    equal = ft_strchr(node->value, '=');
    if (!equal)
        return;
    key = _substr(node->value, 0, equal - node->value);
    value = ft_strdup(equal + 1);
    if (!key || !value)
        return;
    add_var(env_list, key, value);
}
