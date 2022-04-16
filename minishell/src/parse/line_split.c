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

// 큰 따옴표, 작은 따옴표, 스페이스 플래그 변환 함수
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

// 가장 마지막 토큰을 cmd or redirect list에 추가하는 함수
void	line_split_last_arg(char *line, t_env *env, t_list **head[], t_idx *i)
{
	// 만약 마지막 토큰을 처리하지 않았다면 처리함
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

// 토큰을 노드로 만들고, 문자열 idx 옮기는 함수
t_list	*make_node_and_add_index(char *line, t_env *env, t_idx *i)
{
	t_list	*node;

	// 추가할 토큰이 파이프라면, 빈 노드 만들기
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

// 토큰을 노드로 만들어 cmd와 redirect로 구분해 각각의 list에 추가하는 함수
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
		// 파일명이 없거나, 명령어가 없으면 에러
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

// 명령줄을 공백을 기준으로 잘라 각 토큰을 cmd와 redirect로 구분해 각각의 list로 만드는 함수
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
