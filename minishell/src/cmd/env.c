/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:01:29 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 19:03:33 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *start)
{
	if (search_env(start, "PATH") == NULL)
	{
		printf("SnS: env: No such file or directory\n");
		return ;
	}
	display_env(start);
}
