/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:33:31 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 17:27:02 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 파이프 기준으로 나뉜 cmd와 redirect를 하나씩 실행하기 위한 함수
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

// 명령어를 실행하기 위해 생성한 서브 프로세스
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

// 부모 프로세스에서 수행할 일 : fd 변환
void	parent(int pid, int fd[], int idx, int size)
{
	// 마지막 명령어만 기다리고, 나머진 안 기다림
	if (idx < size - 1)
		waitpid(pid, &g_err, WNOHANG);
	else
		waitpid(pid, &g_err, 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

// 자식 프로세스에서 수행할 일 : redirect와 cmd 실행
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
