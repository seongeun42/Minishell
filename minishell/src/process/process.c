/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:33:31 by seongele          #+#    #+#             */
/*   Updated: 2022/03/20 21:34:03 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_redirect_exec(t_list *cmd_head, t_list *redi_head, t_env *env)
{
	t_list		*cmd;
	t_list		*redi;
	t_cmd_flag	f;

	printf("cmd_redirect_exec function in!\n");
	cmd = cmd_head->next;
	redi = redi_head->next;
	f = (t_cmd_flag){1, ft_lstsize(cmd), 1};
	if (f.size == 1)
		return (only_cmd(cmd_head, redi_head, env));
	while (cmd)
	{
		exec_process((char **)cmd->content, (t_list *)redi->content, env, &f);
		cmd = cmd->next;
		redi = redi->next;
	}
	list_free(&cmd_head);
	list_free(&redi_head);
	dup2(BACKUP_STDIN, STDIN_FILENO);
	dup2(BACKUP_STDOUT, STDOUT_FILENO);
	printf("cmd_redirect_exec function out!\n");
	return (OK);
}

int	exec_process(char **cmd, t_list *redirect, t_env *env, t_cmd_flag *flag)
{
	pid_t	pid;
	int		fd[2];

	printf("exec_process function in!\n");
	if (pipe(fd) == -1)
		return (ERR);
	change_stdinout(flag, fd);
	pid = fork();
	if (pid == 0)
		child(cmd, redirect, env, fd);
	else if (pid < 0)
		return (ERR);
	else
		waitpid(pid, NULL, WNOHANG);
	ft_lstclear(&redirect, free);
	double_free(cmd);
	printf("exec_process function out!\n");
	return (OK);
}

// ---------------------

int	parent(t_list *cmd_head, t_list *redi_head, t_env *env)
{
	pid_t	pid;
	int		idx;
	int		**fds;
	int		size;
	t_list	*cmd;
	t_list	*redi;

	cmd = cmd_head->next;
	redi = redi_head->next;
	size = ft_lstsize(cmd);
	fds = (int **)calloc(size - 1, sizeof(int *));
	idx = -1;
	while (++idx < size - 1)
	{
		fds[idx] = (int *)calloc(2, sizeof(int));
		pipe(fds[idx]);
	}
	idx = -1;
	while (++idx < size)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("%d child : %d\n", idx, pid);
			// 두번째 명령어부터는 이전 명령어의 부모와의 파이프로부터 결과 읽어옴
			if (idx > 0)
				dup2(fds[idx - 1][0], STDIN_FILENO);
			// 1 ~ n-1명령어의 결과는 현재 명령어의 부모와의 파이프에 씀
			if (idx < size - 1)
				dup2(fds[idx][1], STDOUT_FILENO);
			else
				// 마지막 명령어의 결과는 표준출력으로
				dup2(BACKUP_STDOUT, STDOUT_FILENO);
			close_pipe(size - 1, &fds, idx);
			if (child2((char **)cmd->content,
				(t_list *)redi->content, env, &fds[idx]) == ERR)
				exit(ERR);
		}
		else if (pid < 0)
			return (ERR);
		else
		{
			printf("%d parent : %d\n", idx, pid);
			if (idx == size - 1)
				waitpid(pid, NULL, 0);
			else
				waitpid(pid, NULL, WNOHANG);
		}
		cmd = cmd->next;
		redi = redi->next;
	}
	close_pipe(size - 1, &fds, -1);
	list_free(&cmd_head);
	list_free(&redi_head);
	dup2(BACKUP_STDIN, STDIN_FILENO);
	dup2(BACKUP_STDOUT, STDOUT_FILENO);
	return (OK);
}

int	child2(char **cmd, t_list *redirect, t_env *env, int **fd)
{
	if (exec_redirect(redirect, *fd) == ERR)
		return (ERR);
	if (command(cmd, env) == ERR)
		return (ERR);
	close(*(fd[0]));
	close(*(fd[1]));
	return (OK);
}

int	close_pipe(int idx, int ***fdss, int exept)
{
	int	**fds;

	fds = *fdss;
	while (idx--)
	{
		if (idx == exept)
			continue ;
		close(fds[idx][0]);
		close(fds[idx][1]);
	}
	return (OK);
}

//------------------------

int	child(char **cmd, t_list *redirect, t_env *env, int fd[])
{
	printf("child function in!\n");
	// redirect 처리
	if (exec_redirect(redirect, fd) == ERR)
		return (ERR);
	// cmd 처리
	if (command(cmd, env) == ERR)
		return (ERR);
	printf("child function out!\n");
	return (OK);
}

int	change_stdinout(t_cmd_flag *flag, int fd[])
{
	printf("change_stdinout function in!\n");

	// 첫 명령어
	if (flag->isFirst)
	{
		dup2(fd[1], STDOUT_FILENO);
		flag->isFirst = 0;
	}
	// 마지막 명령어
	else if (flag->idx == flag->size)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(BACKUP_STDOUT, STDOUT_FILENO);
	}
	else	// 나머지
	{
		dup2(fd[1], STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
	}
	close(fd[1]);
	close(fd[0]);
	flag->idx += 1;

	printf("change_stdinout function out!\n");
	return (OK);
}

int	only_cmd(t_list *cmd, t_list *redi, t_env *env)
{
	int		fd[2];
	pid_t	pid;
	t_list	*clear_redi;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (child((char **)cmd->next->content,
			(t_list *)redi->next->content, env, fd) == ERR)
			exit(ERR);
	}
	else if (pid < 0)
		return (ERR);
	else
	{
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
	}
	clear_redi = (t_list *)redi->next->content;
	ft_lstclear(&clear_redi, free);
	double_free((char **)cmd->next->content);
	list_free(&cmd);
	list_free(&redi);
	return (OK);
}