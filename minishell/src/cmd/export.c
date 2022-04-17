/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:03:14 by sujo              #+#    #+#             */
/*   Updated: 2022/04/17 17:08:37 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_key(char *str)
{
	int	idx;

	if (str[0] == '=' || ft_isdigit(str[0]))
		return (ERR);
	idx = 0;
	while (str[idx] && str[idx] != '=')
	{
		if (!ft_isalnum(str[idx]) && str[idx] != '_')
			return (ERR);
		idx++;
	}
	return (OK);
}

int	ft_export(t_env *start, char **str)
{
	int	idx;
	int	flag;

	flag = 0;
	if (str[1] == NULL)
		display_export(start);
	else
	{
		idx = 1;
		while (str[idx])
		{
			if (check_key(str[idx]))
				flag = erro_message("not a valid identifier\n",
						"export", str[idx], 1);
			else
				cmd_insert_env_node(&start, str[idx]);
			idx++;
		}
	}
	return (flag);
}
