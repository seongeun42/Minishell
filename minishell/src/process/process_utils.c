/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:11:41 by seongele          #+#    #+#             */
/*   Updated: 2022/03/27 17:07:19 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**make_pipe_space(int size)
{
	int	**fds;
	int	idx;

	fds = (int **)calloc(size, sizeof(int *));
	if (!fds)
		exit(ERR);
	idx = -1;
	while (++idx < size)
		fds[idx] = (int *)malloc(sizeof(int) * 2);
	return (fds);
}

int	free_cmd_list(t_list *cmd)
{
	t_list	*tmp;

	while (cmd)
	{
		tmp = cmd;
		double_free(cmd->content);
		cmd = cmd->next;
		free(tmp);
	}
	free(cmd);
	return (OK);
}

int	free_redirect_list(t_list *redi)
{
	t_list	*tmp;
	t_list	*tmp2;

	while (redi)
	{
		tmp = redi;
		tmp2 = redi->content;
		ft_lstclear(&tmp2, free);
		redi = redi->next;
		free(tmp);
	}
	free(redi);
	return (OK);
}
