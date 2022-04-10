/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:53:11 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 17:56:40 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_err_message(char c)
{
	printf("mini: syntax error near unexpected token '%c'\n", c);
	return (ERR);
}

int	last_chr_check(char *line)
{
	int	size;

	size = ft_strlen(line);
	while (line[--size] == ' ')
		;
	if (line[size] == '<' || line[size] == '>' || line[size] == '|')
		return (parsing_err_message(line[size]));
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
		return (ERRCODE_ABNOMAL_LINE);
	redi_cnt = redirect_pipe_count(line);
	if (line_split(redirect_pipe_space_add(line, redi_cnt), env, head) == ERR)
	{
		ft_lstclear(&(redi->next), free);
		ft_lstclear(&(cmd->next), free);
		free(head);
		return (ERRCODE_ABNOMAL_LINE);
	}
	else
	{
		make_cmd_list(cmd);
		make_redirect_list(redi, ft_lstsize(cmd) - 1);
	}
	free(head);
	return (OK);
}
