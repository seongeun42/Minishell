/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:53:11 by seongele          #+#    #+#             */
/*   Updated: 2022/03/06 18:30:36 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_chr_check(char *line)
{
	int	i;
	int	size;

	size = ft_strlen(line);
	while (line[--size] == ' ')
		;
	if (line[size] == '<' || line[size] == '>' || line[size] == '|')
	{
		printf("Line is unclosed!\n");
		return (ERR);
	}
	return (OK);
}

int	parsing(char *line, t_env *env, t_list *cmd, t_list *redi)
{
	t_list	***head;
	int		redi_cnt;

	head = (t_list ***)malloc(sizeof(t_list **) * 2);
	head[0] = &cmd;
	head[1] = &redi;
	if (last_chr_check(line) == ERR)
		return (ERR);
	redi_cnt = redirect_pipe_count(line);
	if (line_split(redirect_pipe_space_add(line, redi_cnt), env, head) == ERR)
	{
		printf("Redirect or Pipe need a argument!\n");
		ft_lstclear(&(redi->next), free);
		ft_lstclear(&(cmd->next), free);
		return (ERR);
	}
	else
	{
		make_cmd_list(cmd);
		make_redirect_list(redi);
	}
	free(head);
	return (OK);
}
