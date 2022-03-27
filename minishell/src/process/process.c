/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:33:31 by seongele          #+#    #+#             */
/*   Updated: 2022/03/27 14:42:42 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_redirect_exec(t_list *cmd, t_list *redi, t_env *env)
{
	pid_t	pid;
	t_list	*tmp;
	t_list	*tmp2;

	pid = fork();
	if (pid == 0)
		parent(cmd->next, redi->next, env, ft_lstsize(cmd) - 1);
	else if (pid < 0)
		return (ERR);
	else
		wait(NULL);
	while (cmd)
	{
		tmp = cmd;
		double_free(cmd->content);
		cmd = cmd->next;
		free(tmp);
	}
	free(cmd);
	while (redi)
	{
		tmp = redi;
		tmp2 = redi->content;
		ft_lstclear(&tmp2, free);
		redi = redi->next;
		free(tmp);
	}
	free(redi);
	return (OK);
}

int	**make_pipe_space(int size)
{
	int	**fds;
	int	idx;

	fds = (int **)calloc(size, sizeof(int *));
	if (!fds)
		exit(ERR);
	idx = -1;
	while (++idx < size)
		fds[idx] = (int *)malloc(sizeof(int) * 2);
	return (fds);
}

int	parent(t_list *cmd, t_list *redi, t_env *env, int size)
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
		{
			if (idx < size - 1)
				dup2(fds[idx][1], STDOUT_FILENO);
			close(fds[idx][0]);
			close(fds[idx][1]);
			if (exec_redirect((t_list *)redi->content) == ERR)
				return (ERR);
			if (command((char **)cmd->content, env) == ERR)
				return (ERR);
		}
		else if (pid < 0)
			return (ERR);
		else
		{
			if (idx < size - 1)
				waitpid(pid, NULL, WNOHANG);
			else
				waitpid(pid, NULL, 0);
			close(fds[idx][1]);
			dup2(fds[idx][0], STDIN_FILENO);
			close(fds[idx][0]);
		}
		cmd = cmd->next;
		redi = redi->next;
	}
	exit(OK);
	return (OK);
}

int	child(char **cmd, t_list *redirect, t_env *env)
{
	if (exec_redirect(redirect) == ERR)
		return (ERR);
	if (command(cmd, env) == ERR)
		return (ERR);
	return (OK);
}
