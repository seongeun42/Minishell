/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:19:10 by sujo              #+#    #+#             */
/*   Updated: 2022/01/16 14:59:31 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	num_size(int n)
{
	int	digit;
	int	cnt;

	cnt = 1;
	digit = 1;
	while (1)
	{
		n /= 10;
		if (n == 0)
			break ;
		digit *= 10;
		cnt++;
	}
	return (cnt);
}

void	get_str(char *str, int minus, int len, int n)
{
	if (minus == 1)
	{
		str[0] = '-';
		len++;
		while (--len > 0)
		{
			str[len] = (n % 10) + '0';
			n /= 10;
		}
	}
	else
	{
		while (--len >= 0)
		{
			str[len] = (n % 10) + '0';
			n /= 10;
		}
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	int		minus;

	minus = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		minus = 1;
		n *= -1;
	}
	len = num_size(n);
	result = (char *)malloc(len + minus + 1);
	if (!result)
		return (0);
	result[len + minus] = '\0';
	get_str(result, minus, len, n);
	return (result);
}
