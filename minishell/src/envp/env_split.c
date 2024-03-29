/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:07:16 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 14:13:47 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**go_free_split(char **str)
{
	size_t	idx;

	idx = 0;
	while (str[idx])
		free(str[idx++]);
	free(str);
	return (0);
}

static int	count_str_length(char const *str, int start, char end)
{
	int	result;

	result = 0;
	while (str[start] && str[start] != end)
	{
		start++;
		result++;
	}
	return (result);
}

char	**env_split(char const *s, char c)
{
	char	**result;
	int		length;
	int		flag;

	flag = 0;
	if (!s)
		return (0);
	result = (char **)malloc(sizeof(char *) * 3);
	if (!result)
		return (0);
	length = count_str_length(s, 0, c);
	result[0] = ft_substr(s, 0, (size_t)length);
	if (ft_strlen(s) - length == 0)
	{
		flag = 1;
		result[1] = NULL;
	}
	else if (ft_strlen(s) - length == 1)
		result[1] = ft_strdup("");
	else
		result[1] = ft_substr(s, length + 1, ft_strlen(s));
	if (!result[0] || (!flag && !result[1]))
		return (go_free_split(result));
	result[2] = 0;
	return (result);
}
