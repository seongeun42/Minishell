/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:10:35 by seongele          #+#    #+#             */
/*   Updated: 2022/03/06 19:19:36 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_redirect_list(t_list *redi)
{
	t_list	*redirect;
	t_list	*cur;

	redirect = redi;
	cur = redi->next;
	redirect->next = 0;
	split_redi_list(cur, redirect);
	return (OK);
}

void	split_redi_list(t_list *cur, t_list *redirect)
{
	t_list	*start;
	t_list	*end;

	while (cur && cur->next)
	{
		if (!cur->content)
		{
			ft_lstadd_back(&redirect, ft_lstnew(0));
			end = cur;
			cur = cur->next;
			free(end);
			continue ;
		}
		start = cur;
		ft_lstadd_back(&redirect, ft_lstnew(start));
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
}
