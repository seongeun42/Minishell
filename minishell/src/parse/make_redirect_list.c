/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:10:35 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 14:15:09 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 나뉘지 않은 redirect list를 파이프 기준으로 나눠 새로운 list로 만드는 함수
int	make_redirect_list(t_list *redi, int size)
{
	t_list	*redirect;
	t_list	*cur;

	redirect = redi;
	cur = redi->next;
	redirect->next = 0;
	// cmd 개수만큼 redirect의 노드 만듦
	while (size--)
		ft_lstadd_back(&redirect, ft_lstnew(0));
	split_redi_list(cur, redirect->next);
	return (OK);
}

// 현재 노드가 파이프인 경우 free시키고 다음 노드로 넘어가는 함수
static int	pipe_list_free(t_list **cur, t_list **redirect)
{
	t_list	*end;

	if (!(*cur)->content)
	{
		end = *cur;
		*cur = (*cur)->next;
		free(end);
		*redirect = (*redirect)->next;
		return (1);
	}
	return (0);
}

// 새로운 list에 파이프 기준으로 redirect list를 나누어 저장하는 함수
// 파이프가 연속으로 나오는 경우는 redirect 없이 명령어만 존재하는 경우로, 빈 노드로 두면 됨
void	split_redi_list(t_list *cur, t_list *redirect)
{
	t_list	*end;

	while (cur && cur->next)
	{
		if (pipe_list_free(&cur, &redirect))
			continue ;
		redirect->content = cur;
		redirect = redirect->next;
		while (cur->next && cur->next->content)
			cur = cur->next;
		if (cur->next)
		{
			end = cur;
			cur = cur->next->next;
			free(end->next);
			end->next = 0;
		}
	}
	// 마지막 노드고, 파이프라면 free
	if (cur && !cur->next && !cur->content)
		free(cur);
}
