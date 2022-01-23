#include "minishell.h"

t_list	*parsing(char *line, t_env* env_list)
{
	t_list	*str;
	t_list	*cmd;

	str = ft_lstnew(0);
	cmd = ft_lstnew(0);
	line_split(line, env_list, &str);
	// cmd 리스트 만들기

	return (cmd);
}

void	line_split(char *line, t_env *env_list, t_list **head)
{
	t_flag	f;
	int		start;
	int		current;

	f = {1, 1, 0, 0};
	start = 0;
	while (line[start] == ' ')
		++start;
	current = start - 1;
	while (line[++current])
	{
		if (f.space && line[current] == ' ')
		{
			// make_new_node()로 새로운 노드 만들어서 str리스트에 연결
			ft_lstadd_back(head, make_node(line, env_list, start, current));
			start = current + 1;
		}
		else if (line[current] == '"' && !f.bigq && !f.smallq)
		{
			f.bigq = 1;
			f.space = 0;
		}
		else if (line[current] == '"' && f.bigq)
		{
			f.bigq = 0;
			f.space = 1;
		}
		else if (line[current] == '\'' && !f.smallq && !f.bigq)
		{
			f.smallq = 1;
			f.space = 0;
		}
		else if (line[current] == '\'' && f.smallq)
		{
			f.smallq = 0;
			f.space = 1;
		}
	}
	ft_lstadd_back(head, make_node(line, env_list, start, current));
}

// 환경변수의 경우, 공백or"or'이 나올 때까지를 key로 봄
// export ab=kk라고 했을 때
// echo "abc  $abkk hi"
// 라고 하면 [abc   hi]라고 출력됨
// $abkk로 인식한 것
t_list	*make_node(char *line, t_env *env_list, int start, int end)
{
	char	*value;
	int		i;
	t_flag	f;

	f = {1, 1, 0, 0};
	// 환경변수 치환할 거 생각해서 1024 더 크게 잡았음
	// 환경변수 값이 저거보다 더 크면... 생각해봐야 함..
	// 값 더 크면 새로 동적할당하는 함수 추가..?
	value = (char *)malloc(sizeof(char) * ((end - start) + 1025));
	if (!value)
		return (0);
	i = 0;
	while (start < end)
	{
		if (f.env_chg && line[start] == '$')
			env_substitude(value, env_find(line, env_list, &start), &i);
		else if (line[start] == '"' && !f.bigq && !f.smallq)
			f.bigq = 1;
		else if (line[start] == '"' && f.bigq)
			f.bigq = 0;
		else if (line[start] == '\'' && !f.smallq && !f.bigq)
		{
			f.smallq = 1;
			f.env_chg = 0;
		}
		else if (line[start] == '\'' && f.smallq)
		{
			f.smallq = 0;
			f.env_chg = 1;
		}
		else
			value[i++] = line[start];
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
	env = search_env(env_list, key);
	free(key);
	// 공백을 가리키는 상태에서 밖에서 ++되면 공백 하나 패스하게 되니까
	*start -= 1;
	return(env);
}

void	env_substitude(char *value, char *env, int *i)
{
	char	*tmp;

	tmp = env;
	if (!tmp)
		return ;
	else
		while (*tmp)
			value[(*i)++] = *tmp++;
}

char	*memory_fit(char *value)
{
	char	*new_str;
	int		size;

	size = ft_strlen(value);
	new_str = (char *)malloc(sizeof(char) * (size + 1));
	ft_strlcpy(new_str, value, size + 1);
	free(value);
	return (new_str);
}