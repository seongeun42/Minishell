/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:39:48 by sujo              #+#    #+#             */
/*   Updated: 2022/02/13 18:39:15 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_env *start, char **key)
{
	int idx;

	if (key == NULL)
		return ;
	idx = 0;
	while (key[idx])
	{
		delete_env_node(&start, key[idx]);
		idx++;
	}
}
