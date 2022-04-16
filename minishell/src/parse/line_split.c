/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:02:46 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 17:11:27 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	line_split_flag_change(char c, t_flag *f)
{
	if (c == '"' && !f->bigq && !f->smallq)
	{
		f->bigq = 1;
		f->space = 0;
	}
	else if (c == '"' && f->bigq)
	{
		f->bigq = 0;
		f->space = 1;
	}
	else if (c == '\'' && !f->smallq && !f->bigq)
	{
		f->smallq = 1;
		f->space = 0;
	}
	else if (c == '\'' && f->smallq)
	{
		f->smallq = 0;
		f->space = 1;
	}
}

void	line_split_last_arg(char *line, t_env *env, t_list **head[], t_idx *i)
{
	if (i->start != i->current)
	{
		if (i->filename)
			ft_lstadd_back(head[1],
				make_node(line, env, i->start, i->current));
		else
			ft_lstadd_back(head[0],
				make_node(line, env, i->start, i->current));
	}
}

t_list	*make_node_and_add_index(char *line, t_env *env, t_idx *i)
{
	t_list	*node;

	if (line[i->start] == '|')
	{
		i->pipe_close = 1;
		node = new_node(0, 0);
	}
	else
	{
		i->pipe_close = 0;
		node = make_node(line, env, i->start, i->current);
	}
	while (line[i->current] == ' ')
		++i->current;
	i->start = i->current--;
	return (node);
}

int	line_split_add_node(char *line, t_env *env, t_list ***head, t_idx *i)
{
	if (line[i->start] == '<' || line[i->start] == '>')
	{
		if (i->filename == 1)
			return (parsing_err_message(line[i->start]));
		ft_lstadd_back(head[1], make_node_and_add_index(line, env, i));
		i->filename = 1;
	}
	else if (line[i->start] == '|')
	{
		if (i->filename == 1 || i->pipe_close == 1)
			return (parsing_err_message(line[i->start]));
		ft_lstadd_back(head[0], new_node(0, 0));
		ft_lstadd_back(head[1], make_node_and_add_index(line, env, i));
	}
	else if (i->filename)
	{
		ft_lstadd_back(head[1], make_node_and_add_index(line, env, i));
		i->filename = 0;
	}
	else
		ft_lstadd_back(head[0], make_node_and_add_index(line, env, i));
	return (OK);
}

int	line_split(char *line, t_env *env, t_list ***head)
{
	t_flag	f;
	t_idx	i;

	f = (t_flag){1, 1, 0, 0};
	i.start = 0;
	while (line[i.start] == ' ')
		++i.start;
	i = (t_idx){i.start, i.start - 1, 0, 0};
	while (line[++i.current])
	{
		if (f.space && line[i.current] == ' ')
		{
			if (line_split_add_node(line, env, head, &i) == ERR)
				return (ERR);
		}
		else if (line[i.current] == '"' || line[i.current] == '\'')
			line_split_flag_change(line[i.current], &f);
	}
	line_split_last_arg(line, env, head, &i);
	free(line);
	return (OK);
}
