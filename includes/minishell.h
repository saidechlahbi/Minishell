/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/09/20 13:33:55 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define GREEN "\001\033[1;32m\002"
# define BLUE "\001\033[1;34m\002"
# define YELLOW "\001\033[1;33m\002"
# define RESET "\001\033[0m\002"
# define TRUE 1
# define FALSE 0

typedef struct s_token
{
	char					*value;
	int						type;
	int						is_ambg;
	int						expanded;
	int						inq;
	int						exp;
	int						validex;
	int						has_literal;
	struct s_token			*next;
}							t_token;

enum						e_type
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
	AMBIGIUOS,
	EXPANDED,
	EXPORT,
	INVALID
};

typedef struct s_scanner
{
	t_token					*tokens;
	int						i;
	int						start;
	int						in_squote;
	int						in_dquote;
	int						encapsuled;
	int						has_literal;
}							t_scanner;

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_redirection
{
	char					*file;
	char					*delimiter;
	int						fd;
	int						type;
	int						inq;
	int						is_ambg;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_cmds
{
	int						pid;
	char					*old_cmd;
	char					**cmd;
	t_redirection			*redirection;
	int						type;
	int						executable;
	int						finde;
	char					*for_no_executable;
	int						slash;
	int						write_in;
	int						read_from;
	char					**envp;
	int						printable;
	struct s_cmds			*next;
}							t_cmds;

typedef struct s_garbage
{
	void					*data;
	int						var;
	struct s_garbage		*next;
}							t_garbage;

/*-----------Parsing-------------*/
void						is_amb(t_token *tokens, t_env *env,
								t_garbage **garbage);
t_token						*tokenize(char *input, t_garbage **garbage);
void						has_dollar(t_token *tokens, t_env *env,
								t_garbage **garbage);
t_env						*get_env(char **envp, t_garbage **garbage);
void						lexing(t_token *token);
int							validate_input(t_token *token);
char						*prepdoc(char *input, t_env *env,
								t_garbage **garbage);
int							set_status(int new_status);
char						*prep(char *input, t_env *env, char *encapsulizer,
								t_garbage **garbage);

/*------------Utils-------------*/
int							export_variable(t_env **env, char *arg,
								t_garbage **garbage);
t_env						*find_key(t_env *env, char *key);
int							export_error(char *arg);
void						print_export(t_env *env, t_garbage **garbage);
void						add_var(t_env **head, char *key, char *value,
								t_garbage **garbage);
int							is_builtin(char *s);
char						*randomize(t_garbage **garbage);
char						*exdoc(char *var, t_env *env);
void						new_var(t_token *node, t_env **env_list,
								t_garbage **garbage);
void						remove_quotes(t_token *tokens, char *encapsulizer,
								t_garbage **garbage);
int							split_n_insert(t_token *cur, char *encapsulizer,
								t_garbage **garbage);
void						delimiter(t_token *token);
int							is_expandable2(char c);
int							is_expandable(char c);
int							ft_strcmp(char *s1, char *s2);
char						*_substr(char *str, int start, int len,
								t_garbage **garbage);
int							is_error(char *s);
int							is_operator(char c);
int							is_append(char *s);
int							is_pipe(char *s);
int							ft_isspace(char c);
int							is_op(char *s);
void						ft_putstr_fd(char *s, int fd);
size_t						ft_strlen(const char *str);
char						*ft_strjoin(char const *s1, char const *s2,
								t_garbage **garbage);
char						*ft_strdup(const char *src, t_garbage **garbage);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
char						*ft_strchr(const char *str, int c);
char						*ft_strrchr(const char *str, int c);
char						*ft_strstr(const char *str, const char *target);
void						*ft_calloc(size_t nmemb, size_t size,
								t_garbage **garbage);
int							ft_isalnum(int c);
char						**ft_split(char const *s, char c,
								t_garbage **garbage);
char						*ft_strncpy(char *dest, const char *src, size_t n);
size_t						ft_strlcpy(char *dest, const char *src,
								size_t size);
char						*ft_itoa(long n, t_garbage **garbage);
void						save_data(t_garbage *garbage);
void						ft_bzero(void *s, size_t n);
int							ft_countwords(const char *str);
char						*prep_helper(t_scanner *var, char *input,
								char *expanded, t_garbage **garbage);
char						*expand_exit_status(t_scanner *var, char *input,
								char *expanded, t_garbage **garbage);
void						skip_nodes(t_token **tokens);
int							check_literal(char *str);
char						*custom_prompt(t_env *env, t_garbage **garbage);
t_garbage					*f(t_garbage *garbage);

/*------------built-in-------------*/
int							execute_built_in(t_cmds *cmd, t_env **env,
								t_garbage **garbage);
void						ft_echo(char **args);
int							check_which_built_are(char *cmd);
int							ft_pwd(void);
void						unset(t_env **env, char **args, t_garbage *garbage);
void						print_env(t_env *env);
int							export(t_env **env, char **args,
								t_garbage **garbage);
int							ft_cd(char **args, t_env **env,
								t_garbage **garbage);
int							ft_exit(t_cmds *cmd, t_garbage *garbage);

/*------------execution-------------*/
void						execution(t_token *token, t_env **env,
								t_garbage **garbage);
t_cmds						*splinting_into_proccess(t_token *token,
								char **envp, t_garbage **garbage);
int							fill_by_path(t_cmds *commands, t_env *env,
								t_garbage **garbage);
char						**env_lst_to_char2(t_env *env, t_garbage **garbage);
int							pipes(t_cmds *commands, t_env **env,
								t_garbage **garbage);
int							one_command(t_cmds *commands, t_env **env,
								t_garbage **garbage);
int							herdoc(t_cmds *commands, t_env *env,
								t_garbage **garbage);
int							check_is_built_in(char *cmd);
void						execution_cmd(t_cmds *command, t_env **env,
								t_garbage **garbage);
void						execute_cmd_built_in(t_cmds *commands, t_env **env,
								t_garbage **garbage);
void						open_and_red_and_fill(t_cmds *command, t_env *env,
								t_garbage **garbage);
int							ft_size(t_cmds *commands);
int							check_if_is_it_dir(char *cmd);
void						close_pipes(int *pipefd);
int							wait_commands(int size, t_cmds *cmd,
								t_garbage **garbage);

/*------------redirection-------------*/
int							open_files(t_cmds *command);
int							redirection(t_cmds *command);
void						close_all_fds_fstat(int start);

/*----------flow tools------------*/
t_cmds						*last_for_cmd(t_cmds *lst);
void						add_back_for_cmd(t_cmds **lst, t_cmds *new);
t_redirection				*last_for_redirec(t_redirection *lst);
void						add_back_for_redirec(t_redirection **lst,
								t_redirection *new);
int							count_args_of_cmd(t_token *token);
char						**fill_cmd(t_token *token, t_garbage **garbage);
int							ft_size(t_cmds *commands);

/*----------cleaner tools------------*/
t_garbage					*new_garbage(void *content, t_garbage *garbage);
void						add_back_for_garbage(t_garbage **lst,
								t_garbage *new);
void						*ft_malloc(size_t type, size_t size,
								t_garbage **garbadge);
void						get_out_from_here(t_garbage *garbage, int status);
void						free_all(t_garbage **garbage);
t_cmds						*return_proccess(t_cmds *cmd);
void						kill_proccess(void);

#endif