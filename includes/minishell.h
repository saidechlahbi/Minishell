/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/19 20:27:09 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h> 
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/stat.h>

extern int g_global_signal;

typedef struct s_token
{
	char			*value;
	int				type;
	int				inq;
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
	int executable;
	int pid;
	int write_in;
	int read_from;
	struct s_cmds *next;
}t_cmds;

typedef struct s_garbage
{
	void *data;
	int var;
	struct  s_garbage *next;
}t_garbage;

/*-----------Parsing-------------*/
t_token	*tokenize(char *input, t_garbage **garbage, int *status);
void	has_dollar(t_token *tokens, t_env *env, t_garbage **garbage, int status);
t_env 	*get_env(char **envp, t_garbage **garbage);
void unset(t_env **env, char **args, t_garbage *garbage);
void 	export(t_env **env, char **args);
void	print_env(t_env *env);
void	lexing(t_token *token);
void	print_export(t_env *env);
int		validate_input(t_token *token, int *status);

/*------------Utils-------------*/
void    add_var(t_env **head, char *key, char *value, t_garbage **garbage);
int		is_builtin(char *s);
char    *randomize(t_garbage **garbage);
char    *exdoc(char *var, t_env *env);
void	new_var(t_token *node, t_env **env_list, t_garbage **garbage);
void 	remove_quotes(t_token *tokens, char *encapsulizer, t_garbage **garbage);
void	split_n_insert(t_token *cur, char *encapsulizer, t_garbage **garbage);
void	delimiter(t_token *token);
int		is_expandable2(char c);
int		is_expandable(char c);
int		ft_strcmp(char *s1, char *s2);
char	*_substr(char *str, int start, int len, t_garbage **garbage);
int		is_error(char *s);
int		is_operator(char c);
int		is_append(char *s);
int		ft_isspace(char c);
int		is_op(char *s);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2, t_garbage **garbage);
char	*ft_strdup(const char *src, t_garbage **garbage);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *str, int c);
char 	*ft_strstr(const char *str, const char *target);
void	*ft_calloc(size_t nmemb, size_t size, t_garbage **garbage);
int		ft_isalnum(int c);
char	*ft_itoa(long n, t_garbage **garbage);
char	**ft_split(char const *s, char c, t_garbage **garbage);
char	*ft_strncpy(char *dest, const char *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

/*------------execution-------------*/
void 			execution(t_token *token, t_env *env, int *last_exit_status, t_garbage **garbage);
t_cmds 			*splinting_into_proccess(t_token *token, t_garbage **garbage);
void 			fill_by_path(t_cmds *commands, t_env *env, t_garbage **garbage);
char 			**env_lst_to_char2(t_env *env, t_garbage **garbage);
void 			pipes(t_cmds *commands, char **envp, int *exit_status, t_garbage *garbage);
void 			one_command(t_cmds *commands, char **env, int *exit_status, t_garbage *garbage);
int 			herdoc(t_cmds *commands, int *exit_status, t_garbage *garbage);
int 			check_is_built_in(char *cmd);
void 			execution_cmd(t_cmds *command, char **envp, t_garbage *garbage);
void 			open_and_redirec(t_cmds *command, t_garbage *garbage);
int 			ft_size(t_cmds *commands);

/*------------redirection-------------*/
int 			open_files(t_cmds *command);
void 			redirection(t_cmds *command);
void 			close_all_fds_fstat(int start);

/*----------flow tools------------*/
t_cmds			*last_for_cmd(t_cmds *lst);
void			add_back_for_cmd(t_cmds **lst, t_cmds *new);
t_redirection	*last_for_redirec(t_redirection *lst);
void			add_back_for_redirec(t_redirection **lst, t_redirection *new);

/*----------cleaner tools------------*/
t_garbage	*new_garbage(void *content, t_garbage *garbage);
void	add_back_for_garbage(t_garbage **lst, t_garbage *new);
void *ft_malloc(size_t type, size_t size, t_garbage **garbadge);
void get_out_from_here(t_garbage *garbage, int status);
void free_all(t_garbage **garbage);

//  void reset_terminal(void);

#endif