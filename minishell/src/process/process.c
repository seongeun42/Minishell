/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:33:31 by seongele          #+#    #+#             */
/*   Updated: 2022/03/13 17:32:35 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_redirect_exec(t_list *cmd_head, t_list *redi_head, t_list *env)
{
	t_list	*cmd;
	t_list	*redirect;

	cmd = cmd_head->next;
	redirect = redi_head->next;
	while (cmd)
	{
		parent((char **)cmd->content, (t_list *)redirect->content, env);
		cmd = cmd->next;
		redirect = redirect->next;
	}
	// cmd_head, redi_head free
}

int	parent(char **cmd, t_list *redirect, t_list *env)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		return (ERR);
	pid = fork();
	if (pid == 0)
	{
		
		child(cmd, redirect, env);
	}
	else if (pid < 0)
		return (ERR);
	else
		waitpid(pid, &status, WNOHANG);
	return (OK);
}

int	child(char **cmd, t_list *redirect, t_list *env)
{
	// redirect 처리
	// cmd 처리
	// redirect, cmd free
}