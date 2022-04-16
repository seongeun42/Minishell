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

// 나뉘지 않은 cmd list를 파이프 기준으로 나눠 cmd 배열을 만들고 list로 만드는 함수
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
		// cmd list에 하나의 명령어를 담은 노드 추가
		ft_lstadd_back(&cmd, ft_lstnew(make_cmd_array(cur)));

		// 파이프가 나오거나 리스트가 끝날 때까지 노드를 넘겨줌
		while (cur && cur->content)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}

		// 노드가 존재하면, 파이프 노드라는 뜻이므로 free시키고 다음 노드로 넘어감
		if (cur)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
	}
	return (OK);
}

// list로 되어 있는 cmd를 하나의 cmd 배열로 만드는 함수
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
		// 만약 환경 변수 치환으로 한 번 더 split해야 하는 경우
		if (cur->split)
		{
			// 공백 기준으로 쪼개고, 기존 content는 free함
			tmp = ft_split((char *)cur->content, ' ');
			free(cur->content);
			// 배열 사이즈 조정하고, 값 복사함
			array = array_resize_and_copy(array, tmp, size, &i);
		}
		else
			array[i++] = (char *)cur->content;	// 아니면 그대로 값 복사
		cur = cur->next;
	}
	return (array);
}

// 환경 변수 치환으로 인해 토큰을 한 번 더 split한 경우 배열 크기를 조정하고 기존 배열 복사하는 함수
char	**array_resize_and_copy(char **old, char **strs, int a_size, int *idx)
{
	char	**new_a;
	int		strs_size;
	int		i;
	int		j;

	strs_size = 0;
	// 추가할 문자 개수 셈
	while (strs[strs_size])
		++strs_size;
	
	// 새로운 배열 동적할당
	new_a = (char **)ft_calloc(a_size + strs_size + 1, sizeof(char *));
	if (!new_a)
		return (0);

	// 기존 배열 그대로 옮기기
	i = -1;
	while (old[++i])
		new_a[i] = old[i];
	
	// 추가할 문자들 복사
	j = -1;
	while (strs[++j])
		new_a[i + j] = strs[j];
	*idx += j;
	free(old);
	free(strs);
	return (new_a);
}

// 파이프 기준으로 나눠 하나의 명령어 사이즈 세는 함수
int	count_size(t_list *cur)
{
	t_list	*list;
	int		cnt;

	list = cur;
	cnt = 0;
	// pipe 노드는 content가 null이므로,
	// 노드가 있고, 노드의 content도 있을 때까지만 셈
	while (list && list->content)
	{
		++cnt;
		list = list->next;
	}
	return (cnt);
}
