/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:21:26 by sujo              #+#    #+#             */
/*   Updated: 2022/01/16 17:30:14 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// env에 담겨져 있는 내용을 출력
void	display_env(t_env *start)
{
	t_env	*ptr;

	ptr = start;
	while (ptr != NULL)
	{
		printf("%s = %s\n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
}

// 새로운 노드를 정상적으로 생성하면 0, 아니면 1 리턴
int	env_insert_node(t_env **start, char *key_, char *value_)
{
	t_env	*new_node;
	t_env	*ptr;

	ptr = *start;
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == 0)
		return (1);
	new_node->next = NULL;
	new_node->key = key_;
	new_node->value = value_;
	if (*start == NULL)
		*start = new_node;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new_node;
	}
	return (0);
}

// env가 정상적으로 파싱되면 0 리턴, 오류가 발생하면 1 리턴
int	env_parsing(char *envp[], t_env **list)
{
	char	**tmp;

	while (*envp)
	{
		tmp = env_split((const char *)*envp, '=');
		if (tmp == 0)
			return (1);
		if (env_insert_node(list, tmp[0], tmp[1]))
			return (1);
		envp++;
	}
	return (0);
}

/*
void env_parsing(char *envp[], t_env *env_list)
파싱 만들기
[함수]
- 노드 생성 함수
- 노드 탐색 함수
- PATH 추출 함수
*/
