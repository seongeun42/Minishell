/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 19:57:14 by sujo              #+#    #+#             */
/*   Updated: 2021/05/05 12:01:02 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *ptr;

	ptr = NULL;
	while (1)
	{
		if (*s == (char)c)
			ptr = (char*)s;
		if (*s == '\0')
			break ;
		s++;
	}
	return (ptr);
}
