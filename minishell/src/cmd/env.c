/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:01:29 by sujo              #+#    #+#             */
/*   Updated: 2022/04/17 17:03:55 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *start)
{
	if (search_env(start, "PATH") == NULL)
		return (erro_message("No such file or directory\n", "env", NULL, 1));
	display_env(start);
	return (OK);
}
