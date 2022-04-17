/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:06:16 by sujo              #+#    #+#             */
/*   Updated: 2022/04/17 17:01:04 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_argu(char **cmd)
{
	int	idx;

	idx = 1;
	while (cmd[idx])
		idx++;
	return (idx);
}

static int	argu_is_num(char *str)
{
	int	idx;

	idx = 0;
	if (str[idx] == '+' || str[idx] == '-')
		idx++;
	while (str[idx])
	{
		if (!ft_isdigit(str[idx]))
			return (0);
		idx++;
	}
	return (1);
}

static long long	ato_ll(char *str)
{
	unsigned long long	result;
	int					minus;

	result = 0;
	minus = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = 1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
		result = result * 10 + (*str++ - '0');
	if (result > LL_MAX && minus == 0)
		return (-1);
	if (result - 1 > LL_MAX && minus == 1)
		return (-1);
	if (minus == 1)
		return (256 - (result % 256));
	return (result % 256);
}

int	ft_exit(char **cmd)
{
	int	size;
	int	is_num;
	int	result;

	size = count_argu(cmd);
	is_num = 1;
	if (size == 1)
		return (OK);
	if (size >= 2)
		is_num = argu_is_num(cmd[1]);
	if (!is_num)
		exit(erro_message("numeric argument required\n", "exit", cmd[1], 255));
	if (size > 2)
		return (erro_message("too many arguments\n", "exit", NULL, 1));
	result = ato_ll(cmd[1]);
	if (result != -1)
		exit(result);
	exit(erro_message("numeric argument required\n", "exit", cmd[1], 255));
}
