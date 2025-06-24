/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/21 17:08:12 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_token
{
	char			*value;
	int				type;
	int				nop;
	struct s_token	*next;
}	t_token;

enum e_type
{
	WORD,
	CMD,
	ARG,
	BUILTIN,
	IN_FILE,
	OUT_FILE,
	PIPE,
	RED_OUT,
	RED_IN,
	HERE_DOC,
	DELIMITER,
	APPEND,
	AMBIGIUOS
};

typedef struct s_fds
{
	int	pipefd1[2];
	int	pipefd2[2];
}	t_fds;

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
void	print_env(t_env *env);

/*------------Utils-------------*/
int		is_builtin(char *s);
char    *randomize();
void	new_var(t_token *node, t_env **env_list);
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