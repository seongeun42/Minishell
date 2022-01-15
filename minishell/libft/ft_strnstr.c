/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:22:19 by sujo              #+#    #+#             */
/*   Updated: 2021/05/05 21:04:23 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	char	*ptr;
	char	*start;
	size_t	idx;
	size_t	idx_tmp;

	idx = 0;
	if (!*find)
		return ((char *)str);
	while (*str && idx < len)
	{
		if (*str == *find)
		{
			start = (char *)find;
			ptr = (char *)str;
			idx_tmp = idx;
			while (*ptr++ == *start && idx_tmp++ < len && *start)
				start++;
			if (!*start)
				return ((char *)str);
		}
		str++;
		idx++;
	}
	return (0);
}
