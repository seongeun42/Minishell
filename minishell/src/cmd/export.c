/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:03:14 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 14:37:42 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_key(char *str)
{
	int	idx;

	if (str[0] == '=')
		return (ERR);
	idx = 0;
	while (str[idx] && str[idx] != '=')
	{
		if (!ft_isalnum(str[idx]))
			return (ERR);
		idx++;
	}
	return (OK);
}

int	ft_export(t_env *start, char **str)
{
	int	idx;

	if (str[1] == NULL)
		display_export(start);
	else
	{
		idx = 1;
		while (str[idx])
		{
			if (check_key(str[idx]))
				printf("bash: export: '%s': not a valid identifier\n", str[idx]);
			else
				cmd_insert_env_node(&start, str[idx]);
			idx++;
		}
	}
	return (OK);
}
