/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:52:08 by sujo              #+#    #+#             */
/*   Updated: 2022/02/20 16:46:42 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exist_env(t_env *start, char *key_)
{
	int		len;
	t_env	*ptr;

	len = ft_strlen(key_) + 1;
	ptr = start;
	while (ptr->next != NULL && ft_strncmp(ptr->key, key_, len) != 0)
		ptr = ptr->next;
	if (ft_strncmp(ptr->key, key_, len) == 0)
		return (1);
	else
		return (0);
}

// 새로운 노드 추가, 성공 시 node, 실패 시 nul
t_env	*create_env_new_node(char *key_, char *value_)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == 0)
		return (0);
	new_node->next = NULL;
	new_node->key = key_;
	new_node->value = NULL;
	if (value_ != NULL)
		new_node->value = value_;
	return (new_node);
}

void	update_env_node(t_env *start, char *key_, char *value_)
{
	int		len;
	t_env	*ptr;

	len = ft_strlen(key_) + 1;
	ptr = start;
	while (ptr->next != NULL && ft_strncmp(ptr->key, key_, len) != 0)
		ptr = ptr->next;
	if (value_ != NULL)
	{
		if (ptr->value != NULL)
			free(ptr->value);
		ptr->value = value_;
	}
	free(key_);
}

void	insert_new_env_node(t_env *start, t_env *new_node)
{
	t_env	*ptr;

	ptr = start;
	if (start == NULL)
		start = new_node;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new_node;
	}
}

int	cmd_insert_env_node(t_env **start, char *str)
{
	char	**pair;
	char	*key;
	char	*value;
	t_env	*new_node;
	t_env	*ptr;

	ptr = *start;
	pair = env_split((const char *)str, '=');
	key = ft_strdup(pair[0]);
	value = ft_strdup(pair[1]);
	if (key == 0)
		return (ERR);
	if (exist_env(*start, key))
		update_env_node(*start, key, value);
	else
	{
		new_node = create_env_new_node(key, value);
		insert_new_env_node(*start, new_node);
	}
	double_free(pair);
	return (OK);
}
