/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:03:14 by sujo              #+#    #+#             */
/*   Updated: 2022/03/20 18:42:46 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (cmd_insert_env_node(&start, str[idx]))
				return (ERR);
			idx++;
		}
	}
	return (OK);
}
