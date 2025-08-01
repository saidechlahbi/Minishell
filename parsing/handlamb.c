/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlamb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:56:51 by schahir           #+#    #+#             */
/*   Updated: 2025/08/01 23:02:59 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	prepamb(char *input, t_env *env, t_garbage **garbage)
{
	char		*expanded;
	char		*value;
	t_scanner	v;

	expanded = ft_strdup("", garbage);
	ft_bzero(&v, sizeof(v));
	while (input[v.i])
	{
		expanded = expand_exit_status(&v, input, expanded, garbage);
		if (input[v.i] == '$' && !v.in_squote && !v.in_dquote
			&& is_expandable(input[v.i + 1]))
		{
			expanded = prep_helper(&v, input, expanded, garbage);
			value = exdoc(_substr(input, v.start, v.i - v.start, garbage), env);
			if (value)
				expanded = ft_strjoin(expanded, value, garbage);
			v.start = v.i;
		}
		else
			v.i++;
	}
	if (v.i > v.start)
		expanded = ft_strjoin(expanded, _substr(input, v.start, v.i - v.start,
					garbage), garbage);
	return (ft_countwords(expanded));
}

void	is_amb(t_token *tokens, t_env *env, t_garbage **garbage)
{
	t_token	*cur;

	cur = tokens;
	while (cur)
	{
		if (cur->type == IN_FILE || cur->type == OUT_FILE
			|| cur->type == APP_FILE)
		{
			if (ft_strchr(cur->value, '$') && prepamb(cur->value, env,
					garbage) != 1)
				cur->is_ambg = AMBIGIUOS;
		}
		cur = cur->next;
	}
}

void	skip_nodes(t_token **tokens)
{
	t_token	*cur;
	t_token	*prev;
	t_token	*next;

	cur = *tokens;
	prev = NULL;
	while (cur)
	{
		next = cur->next;
		if (cur->value && !cur->value[0] && !cur->has_literal)
		{
			if (prev)
				prev->next = next;
			else
				*tokens = next;
		}
		else
			prev = cur;
		cur = next;
	}
	if (!(*tokens))
		set_status(0);
}
