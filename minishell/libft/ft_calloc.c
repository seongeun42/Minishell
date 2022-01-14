/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42soul.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:32:02 by sujo              #+#    #+#             */
/*   Updated: 2021/05/07 11:21:03 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char *result;

	result = (unsigned char *)malloc(nmemb * size);
	if (!result)
		return (0);
	ft_memset(result, 0, nmemb * size);
	return (result);
}
