/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:56:57 by seongele          #+#    #+#             */
/*   Updated: 2022/02/13 17:41:14 by seongele         ###   ########.fr       */
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
		return (0);
	ft_strlcpy(new_value, value, size + 1);
	free(value);
	return (new_value);
}

void	double_free(char **str)
{
	size_t i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}