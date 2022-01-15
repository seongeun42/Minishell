/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:15:11 by sujo              #+#    #+#             */
/*   Updated: 2021/05/06 21:16:27 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			idx;

	ptr1 = (unsigned char *)d;
	ptr2 = (unsigned char *)s;
	idx = 0;
	while (idx < n)
	{
		ptr1[idx] = ptr2[idx];
		if (ptr2[idx] == (unsigned char)c)
			return (d + idx + 1);
		idx++;
	}
	return (0);
}
