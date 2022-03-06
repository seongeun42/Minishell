/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_array_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:21:35 by seongele          #+#    #+#             */
/*   Updated: 2022/03/06 19:11:24 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_cmd_list(t_list *cmd_list)
{
	t_list	*cmd;
	t_list	*cur;
	t_list	*tmp;

	cmd = cmd_list;
	cur = cmd_list->next;
	cmd->next = 0;
	while (cur)
	{
		ft_lstadd_back(&cmd, ft_lstnew(make_cmd_array(cur)));
		while (cur && cur->content)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
		if (cur)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
	}
	return (OK);
}

char	**make_cmd_array(t_list *list)
{
	t_list	*cur;
	char	**array;
	char	**tmp;
	int		size;
	int		i;

	cur = list;
	size = count_size(cur);
	array = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return (0);
	i = 0;
	while (cur && cur->content)
	{
		if (cur->split)
		{
			tmp = ft_split((char *)cur->content, ' ');
			free(cur->content);
			array = array_resize_and_copy(array, tmp, size, &i);
		}
		else
			array[i++] = (char *)cur->content;
		cur = cur->next;
	}
	return (array);
}

char	**array_resize_and_copy(char **old, char **strs, int a_size, int *idx)
{
	char	**new_a;
	int		strs_size;
	int		i;
	int		j;

	strs_size = 0;
	while (strs[strs_size])
		++strs_size;
	new_a = (char **)ft_calloc(a_size + strs_size + 1, sizeof(char *));
	if (!new_a)
		return (0);
	i = -1;
	while (old[++i])
		new_a[i] = old[i];
	j = -1;
	while (strs[++j])
		new_a[i + j] = strs[j];
	*idx += j;
	free(old);
	free(strs);
	return (new_a);
}

int	count_size(t_list *cur)
{
	t_list	*list;
	int		cnt;

	list = cur;
	cnt = 0;
	while (list && list->content)
	{
		++cnt;
		list = list->next;
	}
	return (cnt);
}
