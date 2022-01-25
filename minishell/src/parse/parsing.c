/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:53:11 by seongele          #+#    #+#             */
/*   Updated: 2022/01/23 20:52:57 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parsing(char *line, t_env* env_list)
{
	t_list	*str;
	t_list	*cmd;

	// // test code

	// t_env* tmp;

	// tmp = (t_env *)malloc(sizeof(t_env) * 3);
	// tmp[0].key = "a";
	// tmp[0].value = "aaaa";
	// tmp[1].key = "b";
	// tmp[1].value = "hi";
	// tmp[2].key = 0;
	// tmp[2].value = 0;
	// str = ft_lstnew(0);
	// cmd = ft_lstnew(0);
	// line_split(line, env_list, &str);
	// // cmd 리스트 만들기

	// printf("str size: %d\n", ft_lstsize(str));
	// t_list *cur = str->next;
	// for (int i = 0; cur; i++)
	// {
	// 	printf("%d: %s\n", i, (char *)cur->content);
	// 	cur = cur->next;
	// }

	return (cmd);
}

static void	line_split_flag_change(char c, t_flag* f)
{
	if (c == '"' && !f->bigq && !f->smallq)
	{
		f->bigq = 1;
		f->space = 0;
	}
	else if (c == '"' && f->bigq)
	{
		f->bigq = 0;
		f->space = 1;
	}
	else if (c == '\'' && !f->smallq && !f->bigq)
	{
		f->smallq = 1;
		f->space = 0;
	}
	else if (c == '\'' && f->smallq)
	{
		f->smallq = 0;
		f->space = 1;
	}
}


static void	make_node_flag_change(char c, t_flag* f, char *value, int *i)
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

void	line_split(char *line, t_env *env_list, t_list **head)
{
	t_flag	f;
	int		start;
	int		current;

	f = (t_flag){1, 1, 0, 0};
	start = 0;
	while (line[start] == ' ')
		++start;
	current = start - 1;
	while (line[++current])
	{
		if (f.space && line[current] == ' ')
		{
			ft_lstadd_back(head, make_node(line, env_list, start, current));
			while (line[current] == ' ')
				++current;
			start = current;
			--current;
		}
		else if (line[current] == '"' || line[current] == '\'')
			line_split_flag_change(line[current], &f);
	}
	if (start != current)
		ft_lstadd_back(head, make_node(line, env_list, start, current));
}

t_list	*make_node(char *line, t_env *env_list, int start, int end)
{
	char	*value;
	int		i;
	t_flag	f;

	f = (t_flag){1, 1, 0, 0};
	value = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!value)
		return (0);
	i = 0;
	while (start < end)
	{
		if (f.env_chg && line[start] == '$')
			value = env_substitude(value,
				env_find(line, env_list, &start), &i, end - start);
		else
			make_node_flag_change(line[start], &f, value, &i);
		++start;
	}
	value[i] = 0;
	value = memory_fit(value);
	return (ft_lstnew(value));
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
	key = (char *)malloc(sizeof(char) * (*start - i));
	if (!key)
		return (0);
	j = -1;
	while (++i < *start)
		key[++j] = line[i];
	key[++j] = 0;
	printf("key: %s\n", key);
	env = search_env(env_list, key);
	printf("v: %s\n", env);
	free(key);
	// 공백을 가리키는 상태에서 밖에서 ++되면 공백 하나 패스하게 되니까
	*start -= 1;
	return(env);
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
		new_v = (char *)malloc(sizeof(char) * (size + ft_strlen(env) + 1));
		ft_strlcpy(new_v, value, *i + 1);
		ft_strlcat(new_v, env, size + ft_strlen(env) * 2);
		*i += ft_strlen(env) + 1;
		free(value);
	}
	return (new_v);
}

char	*memory_fit(char *value)
{
	char	*new_value;
	int		size;

	size = ft_strlen(value);
	new_value = (char *)malloc(sizeof(char) * (size + 1));
	ft_strlcpy(new_value, value, size + 1);
	free(value);
	return (new_value);
}