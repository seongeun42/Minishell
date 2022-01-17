/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:50:23 by seongele          #+#    #+#             */
/*   Updated: 2021/05/08 11:55:56 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	all_del(t_list *lst, void (*d)(void *))
{
	t_list	*del_node;

	while (lst)
	{
		del_node = lst;
		lst = lst->next;
		ft_lstdelone(del_node, d);
	}
}

t_list		*ft_lstmap(t_list *s, void *(*f)(void *), void (*d)(void *))
{
	t_list	*new_list;
	t_list	*new_head;

	if (!s)
		return (0);
	new_list = ft_lstnew(f(s->content));
	if (!new_list)
		return (0);
	new_head = new_list;
	s = s->next;
	while (s)
	{
		new_list->next = ft_lstnew(f(s->content));
		if (!new_list->next)
		{
			all_del(new_head, d);
			return (0);
		}
		new_list = new_list->next;
		s = s->next;
	}
	return (new_head);
}
