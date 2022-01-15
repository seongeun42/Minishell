/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:02:02 by sujo              #+#    #+#             */
/*   Updated: 2021/05/03 21:24:05 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t idx;

	idx = 0;
	while (*dest && idx < size)
	{
		dest++;
		idx++;
	}
	while (*src && idx + 1 < size)
	{
		*dest = *src;
		dest++;
		src++;
		idx++;
	}
	if (idx < size)
		*dest = '\0';
	while (*src)
	{
		src++;
		idx++;
	}
	return (idx);
}
