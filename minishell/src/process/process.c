/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:33:31 by seongele          #+#    #+#             */
/*   Updated: 2022/03/20 16:11:10 by seongele         ###   ########.fr       */
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
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child((char **)cmd->next->content, (t_list *)redi->next->content, env, 0);
	else if (pid < 0)
		return (ERR);
	else
		wait(NULL);
	list_free(&cmd);
	list_free(&redi);
	return (OK);
}