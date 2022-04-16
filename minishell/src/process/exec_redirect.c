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

// redirect 수행하는 함수
int	exec_redirect(t_list *redirect)
{
	t_list	*redi;

	// redirect가 없으면 끝
	if (!redirect)
		return (OK);
	redi = redirect;
	while (redi)
	{
		// 파일명이 split을 해야 한다면 에러 처리
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

// << 처리 함수
int	heredoc(char *eof)
{
	char	buf[101];
	int		size;
	int		fd[2];

	// heredoc에 쓸 파이프 생성
	if (pipe(fd) == -1)
		exit(ERR);
	while (1)
	{
		// 백업해둔 표준입출력을 통해 입력 받아옴
		write(BACKUP_STDOUT, "> ", 2);
		size = read(BACKUP_STDIN, buf, 100);
		buf[size - 1] = 0;
		// 입력받은 문자가 eof와 일치하지 않으면
		if (ft_strncmp(buf, eof, ft_strlen(buf) + 1))
		{
			// heredoc 파이프의 쓰기 부분에 입력 받은 내용 쓰기
			write(fd[1], buf, ft_strlen(buf));
			write(fd[1], "\n", 1);
		}
		else
			break ;	// 일치하면 입력 받기 종료
	}
	// 쓰기 파이프 닫기
	close(fd[1]);
	// 읽기 파이프를 표준 입력으로 변환하고 닫아줌
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (OK);
}

// <, << 처리 함수
int	input_redirect_exec(char *filename, int mode)
{
	int	in;

	// <<이면 따로 처리
	if (!mode)
		return (heredoc(filename));
	in = open(filename, O_RDONLY);
	if (in == -1)
		exit(ERR);
	// 오픈한 파일을 표준 입력으로 바꾸고 닫아줌
	dup2(in, STDIN_FILENO);
	close(in);
	return (OK);
}

// >, >> 처리 함수
int	output_redirect_exec(char *filename, int mode)
{
	int	out;

	if (!mode)
		out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
		exit(ERR);
	// 오픈한 파일을 표준 출력으로 바꾸고 닫아줌
	dup2(out, STDOUT_FILENO);
	close(out);
	return (OK);
}
