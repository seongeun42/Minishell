/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 23:21:23 by seongele          #+#    #+#             */
/*   Updated: 2022/03/13 17:05:47 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redirect(t_list *redirect)
{
	t_list *redi;

	redi = redirect->next;
	while (redi)
	{
		// 파일명을 쪼개야 하면 에러 처리
		if (redi->next->split)
			return (clear_redirect(redirect, ERR));
		if (!ft_strncmp((char *)redi->content, "<", 3))
			change_stdin((char *)redi->next->content, 1);
		else if (!ft_strncmp((char *)redi->content, "<<", 4))
			change_stdin((char *)redi->next->content, 0);
		else if (!!ft_strncmp((char *)redi->content, ">", 3))
			change_stdout((char *)redi->next->content, 1);
		else
			change_stdout((char *)redi->next->content, 0);
		redi = redi->next->next;
	}
	return (clear_redirect(redirect, OK));
}

int	clear_redirect(t_list *redirect, int mode)
{
	ft_lstclear(redirect, free);
	if (mode == ERR)
		return (ERR);
	return (OK);
}

int	heredoc(char *eof)
{

}

int	change_stdin(char *filename, int mode)
{
	int	in;

	if (!mode)
		return (heredoc(filename));
	in = open(filename, O_RDONLY);
	if (in == -1)
		return (ERR);
	dup2(in, 0);
	close(in);
	return (OK);
}

int	change_stdout(char *filename, int mode)
{
	int	out;

	if (!mode)
		out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
		return (ERR);
	dup2(out, 1);
	close(out);
	return (OK);
}