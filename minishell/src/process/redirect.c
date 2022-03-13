/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 23:21:23 by seongele          #+#    #+#             */
/*   Updated: 2022/03/13 14:33:51 by seongele         ###   ########.fr       */
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
			return (ERR);
		if (!ft_strncmp((char *)redi->content, "<", 3))
		{

		}
		else if (!ft_strncmp((char *)redi->content, "<<", 4))
		{

		}
		else if (!!ft_strncmp((char *)redi->content, ">", 3))
		{

		}
		else
		{

		}
		redi = redi->next->next;
	}
	return (OK);
}

int	clear_redirect()
{

}

void	heredoc(char *argv[])
{

}

void	open_infile(int pfd[])
{

}

void	open_outfile(int fd[])
{
	
}