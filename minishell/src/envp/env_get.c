/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:15:56 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 14:58:25 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_count_node(t_env *env)
{
	int		idx;
	t_env	*ptr;

	idx = 0;
	ptr = env;
	while (ptr)
	{
		idx++;
		ptr = ptr->next;
	}
	return (idx);
}

static char	*combin_key_value(char *key, char *value)
{
	int		size;
	char	*str;

	size = ft_strlen(key) + ft_strlen(value) + 1;
	str = (char *)ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (0);
	ft_strlcat(str, key, size + 1);
	ft_strlcat(str, "=", size + 1);
	ft_strlcat(str, value, size + 1);
	return (str);
}

static int	env_copy(t_env *env, char **result)
{
	int		idx;
	t_env	*ptr;

	ptr = env;
	idx = 0;
	while (ptr)
	{
		result[idx] = combin_key_value(ptr->key, ptr->value);
		if (!result[idx])
			return (ERR);
		ptr = ptr->next;
		idx++;
	}
	return (OK);
}

char	**env_get(t_env *env)
{
	int		size;
	char	**result;

	if (!env)
		return (0);
	size = env_count_node(env);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (0);
	if (env_copy(env, result))
	{
		double_free(result);
		return (0);
	}
	else
		return (result);
}
