/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:21:35 by seongele          #+#    #+#             */
/*   Updated: 2022/03/06 16:38:41 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_redirect_list(t_list *redi)
{
	t_list	*redirect;
	t_list	*cur;
	t_list	*start;
	t_list	*end;

	redirect = redi;
	cur = redi->next;
	redirect->next = 0;
	while (cur && cur->next)
	{
		// 새로운 redirect의 시작을 저장하고 리스트에 추가
		start = cur;
		ft_lstadd_back(&redirect, ft_lstnew(start));
		// 파이프가 나오기 전까지 쭉 넘김
		while (cur->next && ft_strncmp((char *)cur->next->content, "|", 5))
			cur = cur->next;
		if (cur->next)
		{
			// cur->next가 |니까 cur는 redirect의 마지막 원소
			end = cur;
			// cur->next는 |니까 cur->next->next로 두 번 넘김
			cur = cur->next->next;
			// 파이프를 담은 리스트는 이제 필요없으니까 free
			free(end->next->content);
			free(end->next);
			// redirect의 마지막 원소는 다음을 가리킬 필요 없으니까 0으로
			end->next = 0;
		}
	}
	return (OK);
}

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
		while (cur && ft_strncmp((char *)cur->content, "|", 5))
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
		// 파이프로 끝났으면 파이프 free해주기
		if (cur)
		{
			tmp = cur;
			// 다음 cmd 시작 노드 저장
			cur = cur->next;
			// 파이프 free
			// free(tmp->content);
			// free(tmp);
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
	while (cur && ft_strncmp((char *)cur->content, "|", 5))
	{
		if (cur->split)
		{
			// 스플릿으로 쪼개야 하면 array 크기 재조정하고 복붙
			tmp = ft_split((char *)cur->content, ' ');
			// free(cur->content);
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
	double_free(old);
	double_free(strs);
	return (new_a);
}

int	count_size(t_list *cur)
{
	t_list	*list;
	int		cnt;

	list = cur;
	cnt = 0;
	while (list && ft_strncmp((char *)list->content, "|", 5))
	{
		++cnt;
		list = list->next;
	}
	return (cnt);
}