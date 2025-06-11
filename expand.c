#include "includes/minishell.h"

char *expand(char *var)
{
	return(getenv(var));
}

char *prep(char *input)
{
	int	in_squote;
	int	i;
	int	start;
	char *expanded;

	in_squote = 0;
	i = 0;
	start = 0;
	expanded = NULL;
	while(input[i])
	{
		if(input[i] == '\'')
			in_squote = !in_squote;
		if(input[i] == '$' && !in_squote)
		{
			expanded = ft_strjoin(expanded, _substr(input, start, i));
			i++;
			start = i;
			if (is_expandable(input[i]))
			{
				while(input[i] && is_expandable2(input[i]))
					i++;
			}
			expanded = ft_strjoin(expanded, expand(_substr(input, start, i - start)));
		}
		start = i;
		expanded = ft_strjoin(expanded, _substr(input, start, i - start));
		i++;
	}
	return (expanded);
}

void	has_dollar(t_token *tokens)
{
	t_token	*cur;

	cur	= tokens;
    while (cur->next)
    {
        if (ft_strchr(cur->value, '$'))
			prep(cur->value);

        cur =  cur->next;
    }
}
