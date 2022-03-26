/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 23:21:23 by seongele          #+#    #+#             */
/*   Updated: 2022/03/20 20:02:02 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redirect(t_list *redirect)
{
	t_list *redi;

	if (!redirect)
		return (OK);
	redi = redirect;
	while (redi)
	{
		if (redi->next->split)
			return (ERR);
		if (!ft_strncmp((char *)redi->content, "<", 3))
			input_redirect_exec((char *)redi->next->content, 1);
		else if (!ft_strncmp((char *)redi->content, "<<", 4))
		{
			printf("heredoc~\n");
			input_redirect_exec((char *)redi->next->content, 0);
			printf("heredoc bye~\n");
		}
		else if (!!ft_strncmp((char *)redi->content, ">", 3))
			output_redirect_exec((char *)redi->next->content, 1);
		else
			output_redirect_exec((char *)redi->next->content, 0);
		redi = redi->next->next;
	}
	return (OK);
}

int	heredoc(char *eof)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		return (ERR);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, eof, ft_strlen(line) + 1))
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		else
			break;
	}
	free(line);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (OK);
}

int	input_redirect_exec(char *filename, int mode)
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