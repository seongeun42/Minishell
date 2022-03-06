/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:53:11 by seongele          #+#    #+#             */
/*   Updated: 2022/03/06 15:19:32 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_chr_check(char *line)
{
	int	i;
	int	size;
	
	size = ft_strlen(line);
	while (line[--size] == ' ')
		;
	if (line[size] == '<' || line[size] == '>' || line[size] == '|')
		return (ERR);
	return (OK);
}

// cmd 리스트와 redirect 리스트로 pipe 단위의 cmd 배열 만들기

t_list	*parsing(char *line, t_env *env_list)
{
	t_list	*cmd;
	t_list	*redi;
	t_list	***head;
	int		redi_cnt;

	// // test code
	t_env* tmp;

	tmp = (t_env *)malloc(sizeof(t_env) * 3);
	tmp[0].key = "a";
	tmp[0].value = "cho hi";
	tmp[0].next = &tmp[1];
	tmp[1].key = "b";
	tmp[1].value = "hi";
	tmp[1].next = &tmp[2];
	tmp[2].key = "c";
	tmp[2].value = "hello";
	tmp[2].next = 0;
	redi = ft_lstnew(0);
	cmd = ft_lstnew(0);
	head = (t_list ***)malloc(sizeof(t_list **) * 2);
	head[0] = &cmd;
	head[1] = &redi;

	// 마지막 문자 확인
	if (last_chr_check(line) == ERR)
	{
		printf("Needs last argument\n");
		return (0);
	}
	// redirect과 pipe 사이에 공백 없으면 넣어주는 처리
	redi_cnt = redirect_pipe_count(line);
	if (line_split(redirect_pipe_space_add(line, redi_cnt), tmp, head) == ERR)
	{
		// redirect 파일명 없으니까 cmd, redirect 리스트 free하기
		printf("No Redirect Filename\n");
		ft_lstclear(&redi, free);
		ft_lstclear(&cmd, free);
		if (!redi && !cmd)
			printf("clear!\n");
		return (0);
	}
	else
	{
		// cmd 리스트 만들기
		make_cmd_list(cmd);
		printf("cmd size: %d\n", ft_lstsize(cmd));
		t_list *cur1 = cmd->next;
		for (int i = 0; cur1; i++)
		{
			printf("%d번째 list\n", i);
			char **ccc = (char **)cur1->content;
			for (int j = 0; ccc[j]; j++)
				printf("%d: %s\n", j, ccc[j]);
			cur1 = cur1->next;
		}

		// redirect 리스트 만들기
		make_redirect_list(redi);
		printf("\nredi size: %d\n", ft_lstsize(redi));
		t_list *cur2 = redi->next;
		for (int i = 0; cur2; i++)
		{
			printf("%d번째 list\n", i);
			t_list *curr = cur2->content;
			for (int j = 0; curr; j++)
			{
				printf("%d: %s, sf:%d\n", j, (char *)curr->content, curr->split);
				curr = curr->next;
			}
			cur2 = cur2->next;
		}
	}

	// cmd, redirect 리스트 확인
	// printf("cmd size: %d\n", ft_lstsize(cmd));
	// t_list *cur1 = cmd->next;
	// for (int i = 0; cur1; i++)
	// {
	// 	printf("%d: %s, sf:%d\n", i, (char *)cur1->content, cur1->split);
	// 	cur1 = cur1->next;
	// }

	// printf("redi size: %d\n", ft_lstsize(redi));
	// t_list *cur2 = redi->next;
	// for (int i = 0; cur2; i++)
	// {
	// 	printf("%d: %s, sf:%d\n", i, (char *)cur2->content, cur2->split);
	// 	cur2 = cur2->next;
	// }
	return (cmd);
}
