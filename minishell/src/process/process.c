/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:33:31 by seongele          #+#    #+#             */
/*   Updated: 2022/04/17 14:26:15 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_redirect_exec(t_list *cmd, t_list *redi, t_env *env)
{
	pid_t	pid;
	t_cre	cre;

	pid = fork();
	cre.cmd = cmd->next;
	cre.redi = redi->next;
	cre.env = env;
	if (pid == 0)
	{
		set_signal_parent();
		sub_process(&cre, ft_lstsize(cre.cmd));
	}
	else if (pid < 0)
		return (ERR);
	else
		wait(&g_err);
	g_err = WEXITSTATUS(g_err);
	free_cmd_list(cmd);
	free_redirect_list(redi);
	return (OK);
}

void	sub_process(t_cre *cre, int size)
{
	pid_t	pid;
	int		idx;
	int		**fds;

	fds = make_pipe_space(size);
	idx = -1;
	while (++idx < size)
	{
		if (pipe(fds[idx]) == -1)
			exit(ERR);
		pid = fork();
		if (pid == 0)
			child(cre, fds[idx], idx, size);
		else if (pid < 0)
			exit(ERR);
		else
			parent(pid, fds[idx], idx, size);
		cre->cmd = cre->cmd->next;
		cre->redi = cre->redi->next;
	}
	exit(WEXITSTATUS(g_err));
}

void	parent(int pid, int fd[], int idx, int size)
{
	if (idx < size - 1)
		waitpid(pid, &g_err, WNOHANG);
	else
		waitpid(pid, &g_err, 0);
	close(fd[W]);
	dup2(fd[R], STDIN_FILENO);
	close(fd[R]);
}

void	child(t_cre *cre, int fd[], int idx, int size)
{
	set_signal_child();
	if (idx < size - 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[R]);
	close(fd[W]);
	exec_redirect((t_list *)cre->redi->content);
	command((char **)cre->cmd->content, cre->env);
}
