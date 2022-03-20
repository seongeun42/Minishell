/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 23:21:23 by seongele          #+#    #+#             */
/*   Updated: 2022/03/20 16:13:21 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redirect(t_list *redirect, int fd[])
{
	t_list *redi;

	if (!redirect)
		return (OK);
	redi = redirect->next;
	while (redi)
	{
		// 파일명을 쪼개야 하면 에러 처리
		if (redi->next->split)
			return (clear_redirect(redirect, ERR));
		if (!ft_strncmp((char *)redi->content, "<", 3))
			input_redirect_exec((char *)redi->next->content, fd, 1);
		else if (!ft_strncmp((char *)redi->content, "<<", 4))
			input_redirect_exec((char *)redi->next->content, fd, 0);
		else if (!!ft_strncmp((char *)redi->content, ">", 3))
			output_redirect_exec((char *)redi->next->content, 1);
		else
			output_redirect_exec((char *)redi->next->content, 0);
		redi = redi->next->next;
	}
	return (clear_redirect(redirect, OK));
}

int	clear_redirect(t_list *redirect, int mode)
{
	ft_lstclear(&redirect, free);
	if (mode == ERR)
		return (ERR);
	return (OK);
}

int	heredoc(char *eof, int fd[])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, eof, ft_strlen(line)))
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		else
			break;
	}
	free(line);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	pipe(fd);
	return (OK);
}

int	input_redirect_exec(char *filename, int fd[], int mode)
{
	int	in;

	if (!mode)
		return (heredoc(filename, fd));
	in = open(filename, O_RDONLY);
	if (in == -1)
		return (ERR);
	dup2(in, STDIN_FILENO);
	close(in);
	return (OK);
}

int	output_redirect_exec(char *filename, int mode)
{
	int	out;

	if (!mode)
		out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
		return (ERR);
	dup2(out, STDOUT_FILENO);
	close(out);
	return (OK);
}