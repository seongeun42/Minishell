/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:39:48 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 12:31:57 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env *start, char **key)
{
	int	idx;

	if (key == NULL)
		return (OK);
	idx = 0;
	while (key[idx])
	{
		delete_env_node(&start, key[idx]);
		idx++;
	}
	return (OK);
}
