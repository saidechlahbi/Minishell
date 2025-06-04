/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:46:25 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/02 10:58:42 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_append(char *s)
{
	return(!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, "<<", 2));
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

void	add_token(t_token **head, char *value)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = value;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	validate_input(t_token *token)
{
	t_token	*cur;

	if (!token || !ft_strncmp(token->value, "|", 1))
	{
		ft_putstr_fd("Error : Syntax\n", 2);
		return;
	}
	cur = token;
	while (cur)
	{
		if ((is_op(cur->value) && cur->next &&is_op(cur->next->value)) || (is_op(cur->value) && !cur->next))
		{
			ft_putstr_fd("Error : Syntax\n", 2);
			return;
		}
		cur = cur->next;
	}
}
t_token	*tokenize(char *input)
{
	t_token	*tokens = NULL;
	int		i = 0;
	int		start = 0;
	int		in_squote = 0;
	int		in_dquote = 0;

	while (input[i])
	{
		if (input[i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			i++;
		}
		else if (input[i] == '"' && !in_squote)
		{
			in_dquote = !in_dquote;
			i++;
		}
		else if (!in_squote && !in_dquote && ft_isspace(input[i]))
		{
			if (i > start)
				add_token(&tokens, _substr(input, start, i - start));
			i++;
			while (ft_isspace(input[i]))
				i++;
			start = i;
		}
		else if (!in_squote && !in_dquote && is_operator(input[i]))
		{
			if (i > start)
				add_token(&tokens, _substr(input, start, i - start));
			if (is_append(&input[i]))
			{
				add_token(&tokens, _substr(input, i, 2));
				i += 2;
			}
			else
			{
				add_token(&tokens, _substr(input, i, 1));
				i++;
			}
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		add_token(&tokens, _substr(input, start, i - start));
	
	if (in_squote || in_dquote)
	{
		ft_putstr_fd("Error : Syntax\n", 2);
		return NULL;
	}
	validate_input(tokens);
	return tokens;
}
