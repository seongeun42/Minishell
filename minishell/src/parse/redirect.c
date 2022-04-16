/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:24:09 by seongele          #+#    #+#             */
/*   Updated: 2022/02/20 17:57:51 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 큰 따옴표, 작은 따옴표 플래그 변환 함수
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

// 명령줄 내에 redirect와 pipe가 몇 개 있는지 세는 함수
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

// redirect와 pipe라면 앞뒤를 확인해 공백을 추가하는 함수
void	redirect_pipe_check_and_add(char *new_l, char **l, int *i, char c)
{
	// 첫문자가 아니고 앞의 문자가 공백이 아니면 공백 추가
	if (*i > 0 && new_l[*i - 1] != ' ')
		new_l[(*i)++] = ' ';

	// 기존 문자 복사하고 다음 문자로 이동
	new_l[(*i)++] = *(*l)++;

	// >>, << 이런 경우를 처리하기 위해
	// 다음 문자가 |가 아니고, 문자열 끝도 아니고, 기존 문자와 같다면 복사하고 다음 문자로 이동
	if (c != '|' && **l && **l == c)
		new_l[(*i)++] = *(*l)++;

	// 다음 문자가 문자열 끝이 아니고, 공백도 아니면 공백 추가
	if (**l && **l != ' ')
		new_l[(*i)++] = ' ';
}

// 명령줄 내의 redirect와 pipe 문자 앞뒤에 공백을 추가하는 함수
char	*redirect_pipe_add_space(char *line, int cnt)
{
	t_flag	f;
	char	*new_line;
	int		i;

	// redirect와 pipe가 없으면 명령줄 그대로 리턴
	if (!cnt)
		return (ft_strdup(line));

	f = (t_flag){0, 0, 0, 0};

	// 공백을 추가해 새로 만들 명령줄을 저장할 문자열 배열 동적할당함
	new_line = (char *)ft_calloc(1 + ft_strlen(line) + cnt * 2, sizeof(char));
	if (!new_line)
		return (0);

	i = 0;
	while (*line)
	{
		redirect_pipe_flag_change(&f, *line);
		// >, <, |면 앞뒤 공백과 함께 복사
		if (*line == '<' && !f.bigq && !f.smallq)
			redirect_pipe_check_and_add(new_line, &line, &i, '<');
		else if (*line == '>' && !f.bigq && !f.smallq)
			redirect_pipe_check_and_add(new_line, &line, &i, '>');
		else if (*line == '|' && !f.bigq && !f.smallq)
			redirect_pipe_check_and_add(new_line, &line, &i, '|');
		else
			new_line[i++] = *line++;	// >, <, |가 아니면 그대로 복사
	}

	// 새로운 명령줄의 크기를 딱 맞춰서 리턴함
	return (memory_fit(new_line));
}
