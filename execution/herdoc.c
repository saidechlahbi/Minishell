/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 04:44:31 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/27 20:53:45 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	herdoc_handler(int sig_herdoc __attribute__((unused)))
{
	t_garbage	*garbage;

	garbage = f(NULL);
	get_out_from_here(garbage, 130);
}

static int	read_from_stdin(t_redirection *redirec, int fd, t_env *env,
		t_garbage **garbage)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("Minishell: warning: here-document", 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(redirec->delimiter, 2);
			ft_putstr_fd("')\n", 2);
			return (1);
		}
		if (ft_strcmp(line, redirec->delimiter) == 0)
			return (free(line), 1);
		if (redirec->inq == 0)
			ft_putstr_fd(prepdoc(line, env, garbage), fd);
		else
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

static int	open_herdoc(t_redirection *redirec, int *pid, t_env *env,
		t_garbage **garbage)
{
	int	fd;

	fd = open(redirec->file, O_CREAT | O_WRONLY, 0644);
	redirec->fd = open(redirec->file, O_RDONLY);
	if (redirec->fd == -1 || fd == -1)
		return (perror("open failed\n"), FALSE);
	unlink(redirec->file);
	*pid = fork();
	if (*pid == -1)
		return (set_status(1), perror("fork failed\n"), FALSE);
	if (*pid == 0)
	{
		signal(SIGINT, herdoc_handler);
		signal(SIGQUIT, SIG_IGN);
		read_from_stdin(redirec, fd, env, garbage);
		close_all_fds_fstat(3);
		get_out_from_here(*garbage, 0);
		exit(1);
	}
	return (TRUE);
}

static int	all_herdoc_in_single_cmd(t_redirection *redirec, t_env *env,
		t_garbage **garbage)
{
	int	pid;
	int	status;

	while (redirec)
	{
		if (redirec->type == HERE_DOC)
		{
			g_global_signal = -1;
			status = 0;
			if (open_herdoc(redirec, &pid, env, garbage) == FALSE)
				return (TRUE);
			waitpid(pid, &status, 0);
			if (WEXITSTATUS(status) == 130)
				return (set_status(130), FALSE);
			if (WIFSIGNALED(status))
				return (set_status(WTERMSIG(status) + 128), FALSE);
		}
		redirec = redirec->next;
	}
	set_status(WEXITSTATUS(status));
	return (TRUE);
}

int	herdoc(t_cmds *commands, t_env *env, t_garbage **garbage)
{
	t_redirection	*redirec;

	while (commands)
	{
		redirec = commands->redirection;
		if (!redirec)
		{
			commands = commands->next;
			continue ;
		}
		if (all_herdoc_in_single_cmd(redirec, env, garbage) == TRUE)
			commands = commands->next;
		else
			return (FALSE);
	}
	return (TRUE);
}
