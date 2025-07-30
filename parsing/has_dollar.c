/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:16:04 by schahir           #+#    #+#             */
/*   Updated: 2025/07/30 01:18:42 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	has_dollar(t_token *tokens, t_env *env, t_garbage **garbage)
{
	t_token	*cur;
	t_token	*next;
	char	*expanded;
	char	*encapsulizer;
	char	*last;

	cur = tokens;
	is_amb(cur, env, garbage);
	encapsulizer = randomize(garbage);
	while (cur)
	{
		next = cur->next;
		cur->has_literal = check_literal(cur->value);
		if (ft_strchr(cur->value, '$') && cur->type != DELIMITER
			&& cur->is_ambg != AMBIGIUOS)
		{
			last = ft_strrchr(cur->value, '$');
			expanded = prep(cur->value, env, encapsulizer, garbage);
			cur->value = expanded;
			if (check_last(last) && cur->exp != EXPORT)
				split_n_insert(cur, encapsulizer, garbage);
		}
		cur = next;
	}
	remove_quotes(tokens, encapsulizer, garbage);
}
