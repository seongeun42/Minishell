/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:33:31 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 16:44:49 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_redirect_exec(t_cre *cre_head)
{
	pid_t	pid;
	t_cre	cre;

	pid = fork();
	cre.cmd = cre_head->cmd->next;
	cre.redi = cre_head->redi->next;
	cre.env = cre_head->env;
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
	free_cmd_list(cre_head->cmd);
	free_redirect_list(cre_head->redi);
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
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	child(t_cre *cre, int fd[], int idx, int size)
{
	set_signal_child();
	if (idx < size - 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec_redirect((t_list *)cre->redi->content);
	command((char **)cre->cmd->content, cre->env);
}
