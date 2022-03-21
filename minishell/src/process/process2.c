/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:33:31 by seongele          #+#    #+#             */
/*   Updated: 2022/03/21 13:52:32 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_redirect_exec2(t_list *cmd, t_list *redi, t_env *env)
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
	{
		// printf("%d cmd over wating...\n", pid);
		wait(NULL);
		// printf("cmd over!\n");
	}
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

int	**make_pipe(int size)
{
	int	**fds;
	int	idx;

	fds = (int **)calloc(size, sizeof(int *));
	if (!fds)
		exit(ERR);
	idx = -1;
	while (++idx < size)
	{
		fds[idx] = (int *)malloc(sizeof(int) * 2);
		if (pipe(fds[idx]) == -1)
			exit(ERR);
		// printf("idx pipe : %d, %d\n", fds[idx][0], fds[idx][1]);
	}
	return (fds);
}

int	parent(t_list *cmd, t_list *redi, t_env *env, int size)
{
	pid_t	pid;
	int		idx;
	int		**fds;

	// printf("parent in! cmd size : %d\n", size);
	fds = make_pipe(size);
	idx = -1;
	while (++idx < size)
	{
		pid = fork();
		if (pid == 0)
		{
			char ** ccc = (char **)cmd->content;
			// printf("%d child process : %s\n", idx, ccc[0]);
			// 두번째 명령어부터는 이전 명령어의 부모와의 파이프로부터 결과 읽어옴
			if (idx > 0)
				dup2(fds[idx - 1][0], STDIN_FILENO);
			// 1 ~ n-1명령어의 결과는 현재 명령어의 부모와의 파이프에 씀
			if (idx < size - 1)
				dup2(fds[idx][1], STDOUT_FILENO);
			close_pipe(size, fds, idx);
			if (child2((char **)cmd->content,
				(t_list *)redi->content, env, fds[idx]) == ERR)
				exit(ERR);
		}
		else if (pid < 0)
			return (ERR);
		else
		{
			// printf("%d child process : %d\n", idx, pid);
			if (idx < size - 1)
				waitpid(pid, NULL, WNOHANG);
			else
				waitpid(pid, NULL, 0);
				// wait(NULL);
		}
		cmd = cmd->next;
		redi = redi->next;
	}
	close_pipe(size, fds, -1);
	exit(OK);
	return (OK);
}

int	child2(char **cmd, t_list *redirect, t_env *env, int *fd)
{
	if (exec_redirect(redirect, fd) == ERR)
		return (ERR);
	close(fd[0]);
	close(fd[1]);
	if (command(cmd, env) == ERR)
		return (ERR);
	return (OK);
}

int	close_pipe(int size, int **fds, int last)
{
	int	idx;

	idx = -1;
	while (++idx < size)
	{
		close(fds[idx][0]);
		close(fds[idx][1]);
	}
	return (OK);
}
