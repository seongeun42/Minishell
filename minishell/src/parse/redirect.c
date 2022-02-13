/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:24:09 by seongele          #+#    #+#             */
/*   Updated: 2022/02/13 19:06:47 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_pipe_flag_change(t_flag *f, char c)
{
	if (c == '"' && !f->bigq && !f->smallq)
		f->bigq = 1;
	else if (c == '"' && f->bigq)
		f->bigq = 0;
	else if (c == '\'' && !f->smallq && !f->bigq)
		f->smallq = 1;
	else if (c == '\'' && f->smallq)
		f->smallq = 0;
}

int	redirect_pipe_count(char *line)
{
	t_flag	f;
	int		cnt;

	cnt = 0;
	f = (t_flag){0, 0, 0, 0};
	while (*line)
	{
		redirect_pipe_flag_change(&f, *line);
		if (*line == '<' && !f.bigq && !f.smallq)
		{
			cnt++;
			if (*(line + 1) == '<')
				line++;
		}
		else if (*line == '>' && !f.bigq && !f.smallq)
		{
			cnt++;
			if (*(line + 1) == '>' && !f.bigq && !f.smallq)
				line++;
		}
		else if (*line == '|' && !f.bigq && !f.smallq)
			cnt++;
		line++;
	}
	return (cnt);
}

void	redirect_pipe_check_and_add(char *new_l, char **l, int *i, char c)
{
	if (*i > 0 && new_l[*i - 1] != ' ')
		new_l[(*i)++] = ' ';
	new_l[(*i)++] = *(*l)++;
	if (c != '|' && **l && **l == c)
		new_l[(*i)++] = *(*l)++;
	if (**l && **l != ' ')
		new_l[(*i)++] = ' ';
}

char	*redirect_pipe_space_add(char *line, int cnt)
{
	t_flag	f;
	char	*new_line;
	int		i;

	f = (t_flag){0, 0, 0, 0};
	new_line = (char *)ft_calloc(1 + ft_strlen(line) + cnt * 2, sizeof(char));
	if (!new_line)
		return (0);
	i = 0;
	while (*line)
	{
		redirect_pipe_flag_change(&f, *line);
		if (*line == '<' && !f.bigq && !f.smallq)
			redirect_pipe_check_and_add(new_line, &line, &i, '<');
		else if (*line == '>' && !f.bigq && !f.smallq)
			redirect_pipe_check_and_add(new_line, &line, &i, '>');
		else if (*line == '|' && !f.bigq && !f.smallq)
			redirect_pipe_check_and_add(new_line, &line, &i, '|');
		else
			new_line[i++] = *line++;
	}
	return (memory_fit(new_line));
}
