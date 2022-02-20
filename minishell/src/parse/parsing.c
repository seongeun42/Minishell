/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:53:11 by seongele          #+#    #+#             */
/*   Updated: 2022/02/20 19:30:07 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// redirect과 pipe 사이에 공백 없으면 넣어주는 처리
	redi_cnt = redirect_pipe_count(line);
	line_split(redirect_pipe_space_add(line, redi_cnt), tmp, head);

	// // cmd 리스트 만들기
	printf("cmd size: %d\n", ft_lstsize(cmd));
	t_list *cur1 = cmd->next;
	for (int i = 0; cur1; i++)
	{
		printf("%d: %s, sf:%d\n", i, (char *)cur1->content, cur1->split);
		cur1 = cur1->next;
	}

	printf("redi size: %d\n", ft_lstsize(redi));
	t_list *cur2 = redi->next;
	for (int i = 0; cur2; i++)
	{
		printf("%d: %s, sf:%d\n", i, (char *)cur2->content, cur2->split);
		cur2 = cur2->next;
	}
	return (cmd);
}
