/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:04:36 by seongele          #+#    #+#             */
/*   Updated: 2022/03/06 18:28:07 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
					env_find(line, env_list, &start), &i, end - start);
			if (!f.bigq)
				node_split_flag = 1;
		}
		else
			make_node_flag_change(line[start], &f, value, &i);
		++start;
	}
	return (new_node(memory_fit(value), node_split_flag));
}

t_list	*new_node(char *value, int split_flag)
{
	t_list	*node;

	node = ft_lstnew(value);
	if (split_flag)
		node->split = 1;
	return (node);
}

char	*env_substitude(char *value, char *env, int *i, int size)
{
	char	*tmp;
	char	*new_v;

	tmp = env;
	if (!tmp)
		return (value);
	else
	{
		new_v = (char *)ft_calloc(ft_strlen(value) + size
				+ ft_strlen(env) + 1, sizeof(char));
		ft_strlcpy(new_v, value, *i + 1);
		ft_strlcat(new_v, env, size + ft_strlen(env) * 2);
		*i += ft_strlen(env);
		free(value);
	}
	return (new_v);
}

char	*env_find(char *line, t_env *env_list, int *start)
{
	int		i;
	int		j;
	char	*key;
	char	*env;

	i = *start;
	while (line[*start] && line[*start] != ' '
		&& line[*start] != '\'' && line[*start] != '"')
		++(*start);
	key = (char *)ft_calloc(*start - i, sizeof(char));
	if (!key)
		return (0);
	j = -1;
	while (++i < *start)
		key[++j] = line[i];
	key[++j] = 0;
	env = search_env(env_list, key);
	free(key);
	*start -= 1;
	return (env);
}
