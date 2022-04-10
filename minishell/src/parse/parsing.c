/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:53:11 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 14:14:47 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_chr_check(char *line)
{
	int	size;

	size = ft_strlen(line);
	while (line[--size] == ' ')
		;
	if (line[size] == '<' || line[size] == '>' || line[size] == '|')
	{
		printf("mini: syntax error near unexpected token '%c'\n", line[size]);
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
		return (ERRCODE_ABNOMAl_LINE);
	redi_cnt = redirect_pipe_count(line);
	if (line_split(redirect_pipe_space_add(line, redi_cnt), env, head) == ERR)
	{
		printf("mini: syntax error near unexpected token\n");
		ft_lstclear(&(redi->next), free);
		ft_lstclear(&(cmd->next), free);
		free(head);
		return (ERRCODE_ABNOMAl_LINE);
	}
	else
	{
		make_cmd_list(cmd);
		make_redirect_list(redi, ft_lstsize(cmd) - 1);
	}
	free(head);
	return (OK);
}
