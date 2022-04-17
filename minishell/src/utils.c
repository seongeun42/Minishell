/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:56:57 by seongele          #+#    #+#             */
/*   Updated: 2022/04/17 17:08:02 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*memory_fit(char *value)
{
	char	*new_value;
	int		size;

	size = ft_strlen(value);
	new_value = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_value)
		return (0);
	ft_strlcpy(new_value, value, size + 1);
	free(value);
	return (new_value);
}

void	double_free(char **str)
{
	size_t	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	list_free(t_list **list)
{
	t_list	*curr;
	t_list	*delnode;

	if (!list)
		return ;
	curr = *list;
	while (curr)
	{
		delnode = curr;
		curr = curr->next;
		free(delnode);
	}
	*list = 0;
}

int	erro_message(char *m, char *cmd, char *content, int err)
{
	write(2, "SnS: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 3);
	if (content)
	{
		write(2, content, ft_strlen(content));
		write(2, ": ", 3);
	}
	write(2, m, ft_strlen(m));
	return (err);
}
