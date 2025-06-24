// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipe.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/19 16:43:52 by sechlahb          #+#    #+#             */
// /*   Updated: 2025/06/21 17:13:31 by sechlahb         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// static char **get_paths(t_env *env)
// {
//     char **paths;
    
//     paths = NULL;
//     while (env)
//     {
//         if (ft_strcmp(env->key , "PATH") == 0)
//         {
//             paths = ft_split(env->value, ':');
//             if (!paths)
//                 return NULL;
//             return paths;
//         }
//         env = env->next;
//     }
//     return NULL;
// }

// static char *get_right_path(t_env *env, char *cmd)
// {
//     char **paths;
//     char *cmd_with_path, *str;

//     if (!access(cmd, X_OK))
//         return cmd;
//     paths = get_paths(env);
//     if (!paths)
//         return NULL;
//     while (*paths)
//     {
//         str = ft_strjoin(*paths, "/");
//         cmd_with_path = ft_strjoin(str, cmd);
//         free(str);
//         if (access(cmd_with_path, X_OK) == 0)
//             return (cmd_with_path);
//         free(cmd_with_path);
//         paths++;
//     }
//     return NULL;
// }

// void first_pipe(t_fds fds)
// {
//     int pid = fork();
//     if (pid == 0)
//     { 
//         dup2(fds.pipefd1[1], 1);
//         close(fds.pipefd1[1]);
//         close(fds.pipefd1[0]);
//         close(fds.pipefd2[1]);
//         close(fds.pipefd2[0]);
//         execve(str, ss, NULL);
//     }
//     return;
// }

// void middle_pipe(t_fds fds)
// {
//     int pid = fork();
//     if (pid == 0)
//     {
//         dup2(fds.pipefd1[0], 0);
//         close(fds.pipefd1[1]);
//         close(fds.pipefd1[0]);
//         dup2(fds.pipefd2[1], 1);
//         close(fds.pipefd2[1]);
//         close(fds.pipefd2[0]);
//         execve(str, ss, NULL);
//     }
// }

// void last_pipe(t_fds fds)
// {
//     int pid = fork();
//     if (pid == 0)
//     {
//         dup2(fds.pipefd1[0], 0);
//         close(fds.pipefd1[1]);
//         close(fds.pipefd1[0]);
        

//         close(fds.pipefd2[1]);
//         close(fds.pipefd2[0]);
        
//         char *str = "/bin/wc";
//         char *ss[] = {"wc", "-l", NULL};
//         execve(str, ss, NULL);
//     }
// }

// char **get_(t_token *token)
// {
//     char ***pipes;
//     int start;

//     start = 0;
//     while (token)
//     {
//         if (!ft_strcmp(token->value, "<"))
//     }
// }

// void pipes(t_token *token, t_env *env)
// {
//     t_fds fds;

//     int i = 2;
//     char *cmd = get_right_path(env, );
//     first_pipe()
//     while (i < 2)
//     {
        
//     }
//     last_pipe()
    
// }