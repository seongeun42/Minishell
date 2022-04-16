/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:04:36 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 16:33:31 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 큰 따옴표, 작은 따옴표, 환경변수 치환 여부 플래그 변환
static void	make_node_flag_change(char c, t_flag *f, char *value, int *i)
{
	if (c == '"' && !f->bigq && !f->smallq)
		f->bigq = 1;
	else if (c == '"' && f->bigq)
		f->bigq = 0;
	else if (c == '\'' && !f->smallq && !f->bigq)
	{
		f->smallq = 1;
		f->env_chg = 0;
	}
	else if (c == '\'' && f->smallq)
	{
		f->smallq = 0;
		f->env_chg = 1;
	}
	else
		value[(*i)++] = c;
}

// 새로운 노드를 생성하고 split 여부를 표시하는 함수
t_list	*new_node(char *value, int split_flag)
{
	t_list	*node;

	node = ft_lstnew(value);
	if (split_flag)
		node->split = 1;
	return (node);
}

// 환경 변수 리스트에서 일치하는 환경 변수를 찾는 함수
char	**env_find(char *line, t_env *env_list, int *start)
{
	int		i;
	int		j;
	char	**key_env;

	i = *start;
	while (line[*start] && line[*start] != ' '
		&& line[*start] != '\'' && line[*start] != '"')
		++(*start);
	key_env = (char **)malloc(sizeof(char *) * 2);
	key_env[0] = (char *)ft_calloc(*start - i, sizeof(char));
	if (!key_env[0])
		return (0);
	j = -1;
	while (++i < *start)
		key_env[0][++j] = line[i];
	key_env[0][++j] = 0;
	key_env[1] = search_env(env_list, key_env[0]);
	if (!ft_strncmp(key_env[0], "?", 3))
		key_env[1] = ft_itoa(g_err);
	*start -= 1;
	return (key_env);
}

// 환경 변수를 값으로 치환하는 함수
char	*env_substitude(char *value, char **key_env, int *i)
{
	char	*tmp;
	char	*new_v;

	tmp = key_env[1];
	if (!tmp)
		return (value);
	else
	{
		new_v = (char *)ft_calloc(ft_strlen(value)
				+ ft_strlen(key_env[1]) + 1, sizeof(char));
		ft_strlcpy(new_v, value, *i + 1);
		ft_strlcat(new_v, key_env[1],
			ft_strlen(value) + ft_strlen(key_env[1]) * 2);
		*i += ft_strlen(key_env[1]);
		free(value);
		if (!ft_strncmp(key_env[0], "?", 3))
			free(key_env[1]);
	}
	free(key_env[0]);
	free(key_env);
	return (new_v);
}

// 토큰을 list에 추가할 수 있는 노드로 만드는 함수
t_list	*make_node(char *line, t_env *env_list, int start, int end)
{
	char	*value;
	int		node_split_flag;
	int		i;
	t_flag	f;

	f = (t_flag){1, 1, 0, 0};
	value = (char *)ft_calloc(end - start + 1, sizeof(char));
	if (!value)
		return (0);
	node_split_flag = 0;
	i = 0;
	while (start < end)
	{
		if (f.env_chg && line[start] == '$')
		{
			value = env_substitude(value,
					env_find(line, env_list, &start), &i);
			if (!f.bigq)
				node_split_flag = 1;
		}
		else
			make_node_flag_change(line[start], &f, value, &i);
		++start;
	}
	return (new_node(memory_fit(value), node_split_flag));
}
