/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/17 17:08:52 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	/*
	types ->
		0 -> command
		1 -> operator
		2 -> expandable
		3 -> ambiguous
	*/
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/*-----------Parsing-------------*/
t_token	*tokenize(char *input);
void	has_dollar(t_token *tokens, t_env *env);
t_env	*get_env(char **envp);
void	unset(t_env **env, const char *value);
void	export(t_env *env);

/*------------Utils-------------*/
void	restore_quotes(t_token *tokens);
void	remove_quotes(t_token *tokens);
void	split_n_insert(t_token *cur);
int		is_expandable2(char c);
int		is_expandable(char c);
int		ft_strcmp(char *s1, char *s2);
char	*_substr(char *str, int start, int len);
int		is_operator(char c);
int		is_append(char *s);
int		ft_isspace(char c);
int		is_op(char *s);

#endif