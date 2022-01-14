/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 19:31:49 by sujo              #+#    #+#             */
/*   Updated: 2021/05/05 19:46:51 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	func(long long nbr, int fd)
{
	if (nbr == 0)
		return ;
	func(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr *= -1;
	}
	func(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
}
