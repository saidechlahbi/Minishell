/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:32:32 by schahir           #+#    #+#             */
/*   Updated: 2025/07/23 05:55:02 by schahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	to_skip(t_scanner *var, char *encpasulizer, char *new_val, int *j)
{
	if (!ft_strncmp(&var->tokens->value[var->i], encpasulizer, 19))
	{
		var->i += 19;
		var->encapsuled = !var->encapsuled;
	}
	else if (var->tokens->value[var->i] == '\'' && !var->in_dquote
		&& !var->encapsuled)
	{
		var->in_squote = !var->in_squote;
		var->i++;
	}
	else if (var->tokens->value[var->i] == '"' && !var->in_squote
		&& !var->encapsuled)
	{
		var->in_dquote = !var->in_dquote;
		var->i++;
	}
	else
		new_val[(*j)++] = var->tokens->value[var->i++];
}

void	remove_quotes(t_token *tokens, char *encapsulizer, t_garbage **garbage)
{
	char		*new_val;
	int			j;
	t_scanner	var;

	ft_bzero(&var, sizeof(var));
	var.tokens = tokens;
	while (var.tokens)
	{
		new_val = ft_malloc(1, ft_strlen(var.tokens->value) + 1, garbage);
		var.i = 0;
		j = 0;
		while (var.tokens && var.tokens->value[var.i])
			to_skip(&var, encapsulizer, new_val, &j);
		new_val[j] = 0;
		var.tokens->value = new_val;
		var.tokens = var.tokens->next;
	}
}
/*
void	remove_quotes(t_token *tokens, char *encapsulizer, t_garbage **garbage)
{
	t_token	*cur;
	char	*new_val;

	int in_squote, in_dquote, encapsuled, i, j;
	in_squote = 0;
	in_dquote = 0;
	encapsuled = 0;
	cur = tokens;
	while (cur)
	{
		new_val = ft_malloc(1, ft_strlen(cur->value) + 1, garbage);
		i = 0;
		j = 0;
		while (cur && cur->value[i])
		{
			if (!ft_strncmp(&cur->value[i], encapsulizer, 19))
			{
				i += 19;
				encapsuled = !encapsuled;
			}
			else if (cur->value[i] == '\'' && !in_dquote && !encapsuled)
			{
				in_squote = !in_squote;
				i++;
			}
			else if (cur->value[i] == '"' && !in_squote && !encapsuled)
			{
				in_dquote = !in_dquote;
				i++;
			}
			else
				new_val[j++] = cur->value[i++];
		}
		new_val[j] = 0;
		cur->value = new_val;
		cur = cur->next;
	}
}
*/