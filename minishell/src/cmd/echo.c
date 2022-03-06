/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:14:22 by sujo              #+#    #+#             */
/*   Updated: 2022/03/06 14:45:57 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag_n(char *str)
{
	int	idx;

	if (str[0] != '-')
		return (0);
	idx = 1;
	while (str[idx])
	{
		if (str[idx] != 'n')
			return (0);
		idx++;
	}
	return (1);
}

static int	cmd_cnt(char **cmd)
{
	int	idx;

	idx = 0;
	while (cmd[idx])
		idx++;
	return (idx);
}

static void	print_result(char **cmd, int size, int flag)
{
	int	idx;

	if (flag)
		idx = 2;
	else
		idx = 1;
	while (cmd[idx])
	{
		if (idx == size - 1)
			printf("%s", cmd[idx]);
		else
			printf("%s ", cmd[idx]);
		idx++;
	}
	if (!flag)
		printf("\n");
}

void	ft_echo(char **cmd)
{
	int	size;
	int	flag;

	size = cmd_cnt(cmd);
	if (size == 1)
		printf("\n");
	else
	{
		flag = check_flag_n(cmd[1]);
		print_result(cmd, size, flag);
	}
}
