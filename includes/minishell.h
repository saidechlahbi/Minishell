/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/12 14:59:03 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
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
	APP_FILE,
	PIPE,
	RED_OUT,
	RED_IN,
	HERE_DOC,
	DELIMITER,
	APPEND,
	AMBIGIUOS
};

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;


typedef struct s_redirection
{
	char *file;
	char *delimiter;
	int fd;
	int type;
	struct s_redirection *next;
}t_redirection;

typedef struct s_cmds
{
	char **cmd;
	t_redirection *redirection;
	int type;
	struct s_cmds *next;
	
}t_cmds;

/*-----------Parsing-------------*/
t_token	*tokenize(char *input);
void	has_dollar(t_token *tokens, t_env *env);
t_env	*get_env(char **envp);
void	unset(t_env **env, const char *value);
void	export(t_env *env);
void	print_env(t_env *env);
void	lexing(t_token *token);

/*------------execution-------------*/
t_cmds *splinting_into_proccess(t_token *token);
void fill_by_path(t_cmds *commands, t_env *env);
char **env_lst_to_char2(t_env *env);
void open_files(t_cmds *commands);
void pipes(t_cmds *commands, t_env *env);

/*------------Utils-------------*/
int		is_builtin(char *s);
char    *randomize();
void	new_var(t_token *node, t_env **env_list);
void	restore_quotes(t_token *tokens);
void	remove_quotes(t_token *tokens, char *encapsulizer);
void	split_n_insert(t_token *cur, char *encapsulizer);
int		is_expandable2(char c);
int		is_expandable(char c);
int		ft_strcmp(char *s1, char *s2);
char	*_substr(char *str, int start, int len);
int		is_operator(char c);
int		is_append(char *s);
int		ft_isspace(char c);
int		is_op(char *s);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *str, int c);
char 	*ft_strstr(const char *str, const char *target);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
char	**ft_split(char const *s, char c);
char	*ft_strncpy(char *dest, const char *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);


#endif