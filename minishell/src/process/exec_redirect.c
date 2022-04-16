/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 23:21:23 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 19:03:00 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redirect(t_list *redirect)
{
	t_list	*redi;

	if (!redirect)
		return (OK);
	redi = redirect;
	while (redi)
	{
		if (redi->next->split)
		{
			printf("SnS: ambiguous redirect\n");
			exit(ERR);
		}
		if (!ft_strncmp((char *)redi->content, "<", 3))
			input_redirect_exec((char *)redi->next->content, 1);
		else if (!ft_strncmp((char *)redi->content, "<<", 4))
			input_redirect_exec((char *)redi->next->content, 0);
		else if (!ft_strncmp((char *)redi->content, ">", 3))
			output_redirect_exec((char *)redi->next->content, 1);
		else
			output_redirect_exec((char *)redi->next->content, 0);
		redi = redi->next->next;
	}
	return (OK);
}

int	heredoc(char *eof)
{
	char	buf[101];
	int		size;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(ERR);
	while (1)
	{
		write(BACKUP_STDOUT, "> ", 2);
		size = read(BACKUP_STDIN, buf, 100);
		buf[size - 1] = 0;
		if (ft_strncmp(buf, eof, ft_strlen(buf) + 1))
		{
			write(fd[1], buf, ft_strlen(buf));
			write(fd[1], "\n", 1);
		}
		else
			break ;
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (OK);
}

int	input_redirect_exec(char *filename, int mode)
{
	int	in;

	if (!mode)
		return (heredoc(filename));
	in = open(filename, O_RDONLY);
	if (in == -1)
		exit(ERR);
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
		exit(ERR);
	dup2(out, STDOUT_FILENO);
	close(out);
	return (OK);
}
