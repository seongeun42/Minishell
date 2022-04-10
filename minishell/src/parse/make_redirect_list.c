/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:10:35 by seongele          #+#    #+#             */
/*   Updated: 2022/03/27 19:54:46 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_redirect_list(t_list *redi, int size)
{
	t_list	*redirect;
	t_list	*cur;

	redirect = redi;
	cur = redi->next;
	redirect->next = 0;
	while (size--)
		ft_lstadd_back(&redirect, ft_lstnew(0));
	split_redi_list(cur, redirect->next);
	return (OK);
}

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

void	split_redi_list(t_list *cur, t_list *redirect)
{
	t_list	*start;
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
	if (cur && !cur->next && !cur->content)
		free(cur);
}
