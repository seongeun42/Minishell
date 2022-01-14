/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 01:00:32 by sujo              #+#    #+#             */
/*   Updated: 2021/05/06 19:12:51 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char ch1;
	unsigned char ch2;

	while (n)
	{
		ch1 = (unsigned char)*s1++;
		ch2 = (unsigned char)*s2++;
		if (ch1 != ch2)
			return (ch1 - ch2);
		else if (!ch1)
			break ;
		n--;
	}
	return (0);
}
