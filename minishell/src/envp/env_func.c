/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:37:08 by sujo              #+#    #+#             */
/*   Updated: 2022/02/20 17:08:44 by seongele         ###   ########.fr       */
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
char	*search_env(t_env *start, char *key_)
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
void	delete_env_node(t_env **start, char *key_)
{
	int		len;
	t_env	*ptr;
	t_env	*preptr;

	len = ft_strlen(key_) + 1;
	ptr = *start;
	if (ft_strncmp(ptr->key, key_, len) == 0)
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
		if (ft_strncmp(ptr->key, key_, len) == 0)
		{
			preptr->next = ptr->next;
			free_env_node(ptr);
		}
	}
}

// env에 담겨져 있는 내용을 출력
void	display_env(t_env *start)
{
	t_env	*ptr;

	ptr = start;
	while (ptr != NULL)
	{
		if (ptr->value != NULL)
			printf("%s=%s\n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
}

void	display_export(t_env *start)
{
	t_env	*ptr;

	ptr = start;
	while (ptr != NULL)
	{
		printf("declare -x %s", ptr->key);
		if (ptr->value != NULL)
			printf("=\"%s\"\n", ptr->value);
		else
			printf("\n");
		ptr = ptr->next;
	}
}
