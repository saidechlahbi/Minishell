#include "includes/minishell.h"

int	is_operator(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (RED_OUT);
	else if (c == '<')
		return (RED_IN);
	return (-1);
}

int	is_append(char *s)
{
	if(!ft_strncmp(s, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(s, "<<", 2))
		return (HERE_DOC);
	return (-1);
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

char	*_substr(char *str, int start, int len)
{
	char	*res;

	res = malloc(len + 1);
	if (!res)
		return NULL;
	ft_strncpy(res, str + start, len);
	res[len] = 0;
	return (res);
}

int is_op(char *s)
{
	return (!ft_strncmp(s, "|", 1) || !ft_strncmp(s, ">", 1) 
			|| !ft_strncmp(s, "<", 1) || !ft_strncmp(s, ">>", 2) 
			|| !ft_strncmp(s, "<<", 2));
}

int	is_expandable(char c)
{
	return((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95);
}

int	is_expandable2(char c)
{
	return((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 95);
}

int		ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
