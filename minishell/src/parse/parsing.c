/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:53:11 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 19:02:34 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 파싱 에러 메시지 출력 함수
int	parsing_err_message(char c)
{
	printf("SnS: syntax error near unexpected token '%c'\n", c);
	return (ERR);
}

// 명령줄의 마지막 문자를 확인하는 함수
int	last_chr_check(char *line)
{
	int	size;

	size = ft_strlen(line);
	while (line[--size] == ' ')
		;
	if (line[size] == '<' || line[size] == '>' || line[size] == '|')
		return (parsing_err_message(line[size]));
	return (OK);
}

// 명령줄 parsing을 위한 함수
int	parsing(char *line, t_env *env, t_list *cmd, t_list *redi)
{
	t_list	***head;	// cmd, redirect 리스트의 헤드를 담을 리스트
	int		redi_cnt;

	head = (t_list ***)malloc(sizeof(t_list **) * 2);
	head[0] = &cmd;
	head[1] = &redi;

	// 마지막 문자가 <, >, |인지 확인
	if (last_chr_check(line) == ERR)
		return (ERRCODE_ABNOMAL_LINE);

	// 명령줄 안에 redirect가 몇 개 있는지 셈
	redi_cnt = redirect_pipe_count(line);

	// redirect와 pipe 양 옆에 공백을 추가해 새로 만든 명령줄로 파싱 진행
	// 공백을 기준으로 쪼개며 cmd와 redirect를 구분해서 각각 list로 만들게 됨
	if (line_split(redirect_pipe_add_space(line, redi_cnt), env, head) == ERR)
	{
		// 만약 파싱 에러가 나면 만들어둔 거 free하고 끝
		ft_lstclear(&(redi->next), free);
		ft_lstclear(&(cmd->next), free);
		free(head);
		return (ERRCODE_ABNOMAL_LINE);
	}
	else
	{
		// 파싱이 잘 끝났으면
		// cmd를 파이프 기준으로 나눈 cmd list 만들기
		make_cmd_list(cmd);
		// redirect를 파이프 기준으로 나눈 redirect list 만들기
		make_redirect_list(redi, ft_lstsize(cmd) - 1);
	}
	free(head);
	return (OK);
}
