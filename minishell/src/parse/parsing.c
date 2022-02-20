/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:53:11 by seongele          #+#    #+#             */
/*   Updated: 2022/02/13 19:09:32 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. redirect와 pipe 양 옆에 공백 넣어주는 처리 -> 했음
// 2. parsing 할 때, cmd와 redirect 나눠서 리스트 만들기
// 3. | 나오면 새로운 cmd와 redirect

t_list	*parsing(char *line, t_env *env_list)
{
	t_list	*str;
	t_list	*cmd;
	t_list	*redi;
	int		redi_cnt;

	// // test code
	t_env* tmp;

	tmp = (t_env *)malloc(sizeof(t_env) * 3);
	tmp[0].key = "a";
	tmp[0].value = "cho hi";
	tmp[1].key = "b";
	tmp[1].value = "hi";
	tmp[2].key = 0;
	tmp[2].value = 0;
	str = ft_lstnew(0);
	cmd = ft_lstnew(0);
	// redirect과 pipe 사이에 공백 없으면 넣어주는 처리
	redi_cnt = redirect_pipe_count(line);
	if (redi_cnt)
		// line_split(redirect_pipe_space_add(line, redi_cnt), env_list, &str);
		line_split(redirect_pipe_space_add(line, redi_cnt), tmp, &str);
	else
		// line_split(line, env_list, &str);
		line_split(line, tmp, &str);
	// line_split(line, env_list, &str);

	// // cmd 리스트 만들기

	printf("str size: %d\n", ft_lstsize(str));
	t_list *cur = str->next;
	for (int i = 0; cur; i++)
	{
		printf("%d: %s, sf:%d\n", i, (char *)cur->content, cur->split);
		cur = cur->next;
	}

	return (cmd);
}

static void	line_split_flag_change(char c, t_flag *f)
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

// start, current, filename 구조체 만들어서 줄 수 줄이기
// make_node 부분 함수로 따로 빼기
void	line_split(char *line, t_env *env, t_list **cmd, t_list **redirect)
{
	t_flag	f;
	int		start;
	int		current;
	int		filename;

	f = (t_flag){1, 1, 0, 0};
	start = 0;
	while (line[start] == ' ')
		++start;
	filename = 0;
	current = start - 1;
	while (line[++current])
	{
		// if (f.space && line[current] == ' ')
		// {
		// 	ft_lstadd_back(head, make_node(line, env, start, current));
		// 	while (line[current] == ' ')
		// 		++current;
		// 	start = current--;
		// }
		if (f.space && line[current] == ' ')
		{
			if (line[start] == '<' || line[start] == '>')
			{
				// redirect에 붙이기
				ft_lstadd_back(redi, make_node(line, env_list, start, current));
				while (line[current] == ' ')
					++current;
				start = current--;
				filename = 1;
			}
			else if (line[start] == '|')
			{
				// cmd와 redirect 둘 다 붙이기
				ft_lstadd_back(cmd, make_node(line, env_list, start, current));
				ft_lstadd_back(redi, make_node(line, env_list, start, current));
				while (line[current] == ' ')
					++current;
				start = current--;
			}
			else if (filename)
			{
				// redi에 붙이기
				ft_lstadd_back(redi, make_node(line, env_list, start, current));
				while (line[current] == ' ')
					++current;
				start = current--;
				filename = 0;
			}
			else
			{
				// cmd에 붙이기
				ft_lstadd_back(cmd, make_node(line, env_list, start, current));
				while (line[current] == ' ')
					++current;
				start = current--;
			}
		}
		else if (line[current] == '"' || line[current] == '\'')
			line_split_flag_change(line[current], &f);
	}
	// if (start != current)
	// 	ft_lstadd_back(head, make_node(line, env, start, current));
	if (start != current)
	{
		if (filename)
			ft_lstadd_back(redi, make_node(line, env_list, start, current));
		else
			ft_lstadd_back(cmd, make_node(line, env_list, start, current));
	}
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
	value = memory_fit(value);
	return (new_node(value, node_split_flag));
}

t_list	*new_node(char *value, int split_flag)
{
	t_list	*node;

	node = ft_lstnew(value);
	if (split_flag)
		node->split = 1;
	return (node);
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
	// 공백을 가리키는 상태에서 밖에서 ++되면 공백 하나 패스하게 되니까
	*start -= 1;
	return (env);
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
		new_v = (char *)ft_calloc(size + ft_strlen(env) + 1, sizeof(char));
		ft_strlcpy(new_v, value, *i + 1);
		ft_strlcat(new_v, env, size + ft_strlen(env) * 2);
		*i += ft_strlen(env) + 1;
		free(value);
	}
	return (new_v);
}
