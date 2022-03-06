/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:03:14 by sujo              #+#    #+#             */
/*   Updated: 2022/03/06 14:46:34 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_env *start, char **str)
{
	int	idx;

	if (str == NULL)
		display_export(start);
	else
	{
		idx = 0;
		while (str[idx])
		{
			if (cmd_insert_env_node(&start, str[idx]))
				return (ERR);
			idx++;
		}
	}
	return (OK);
}
