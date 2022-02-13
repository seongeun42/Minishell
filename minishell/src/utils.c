/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:56:57 by seongele          #+#    #+#             */
/*   Updated: 2022/02/13 15:58:10 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*memory_fit(char *value)
{
	char	*new_value;
	int		size;

	size = ft_strlen(value);
	new_value = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_value)
		return ERR;
	ft_strlcpy(new_value, value, size + 1);
	free(value);
	return (new_value);
}