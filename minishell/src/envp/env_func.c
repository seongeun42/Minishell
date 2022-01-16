/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:37:08 by sujo              #+#    #+#             */
/*   Updated: 2022/01/16 18:46:49 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 노드의 메모리 해제
static void	free_env_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

// key_를 토대로 env에서 value를 찾음. 없으면 null번환
char *search_env(t_env *start, char *key_)
{
	int		len;
	t_env	*ptr;

	len = ft_strlen(key_) + 1;
	ptr = start;
	while (ptr->next != NULL && ft_strncmp(ptr->key, key_, len) != 0)
		ptr = ptr->next;
	if (ft_strncmp(ptr->key, key_, len) == 0)
		return (ptr->value);
	else
		return (0);
}

// 환경변수를 삭제하는 경우 key를 중심으로 탐색
void delete_env_node(t_env **start, char *key_)
{
	int		len;
	t_env	*ptr;
	t_env	*preptr;

	len = ft_strlen(key_) + 1;
	ptr = *start;
	if (ft_strncmp(ptr->key, key_, len) != 0)
	{
		*start = (*start)->next;
		free_env_node(ptr);
	}
	else
	{
		while (ptr->next != NULL && ft_strncmp(ptr->key, key_, len) != 0)
		{
			preptr = ptr;
			ptr = ptr->next;
		}
		preptr->next = ptr->next;
		free_env_node(ptr);
	}
}
