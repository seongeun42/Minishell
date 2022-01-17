#include "minishell.h"

t_list	*parsing(char *line)
{
	t_list	*str;
	t_list	*cmd;

	str = ft_lstnew(0);
	cmd = ft_lstnew(0);
	// line_split(line, str);

	return cmd;
}

void	line_split(char *line, t_list *head)
{
	t_flag	flag;
	int		start;
	int		current;

	flag = (t_flag){1, 1, 0, 0};
	start = 0;
	current = -1;

	while(line[++current])
	{
		if (flag[1] && line[current] == ' ')
		{
			// make_new_node()로 새로운 노드 만들어서 str리스트에 연결
			ft_lstadd_back(&head, make_new_node(line, start, current));
			start = current + 1;
		}
		else if (line[current] == '"' && !flag[2] && !flag[3])
		{
			flag[2] = 1;
			flag[1] = 0;
		}
		else if (line[current] == '"' && flag[2])
		{
			flag[2] = 0;
			flag[1] = 1;
		}
		else if (line[current] == '\'' && !flag[3] && !flag[3])
		{
			flag[3] = 1;
			flag[1] = 0;
		}
		else if (line[current] == '\'' && flag[3])
		{
			flag[3] = 0;
			flag[1] = 1;
		}
	}
}

t_list	*make_new_node(char *line, int start, int end)
{
	
}