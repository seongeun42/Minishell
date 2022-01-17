/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:49:49 by seongele          #+#    #+#             */
/*   Updated: 2021/05/06 13:03:11 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*delnode;

	if (!lst || !del)
		return ;
	curr = *lst;
	while (curr)
	{
		delnode = curr;
		curr = curr->next;
		del(delnode->content);
		free(delnode);
	}
	*lst = 0;
}
