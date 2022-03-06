/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:51:16 by sujo              #+#    #+#             */
/*   Updated: 2022/02/20 19:18:16 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	int		size;
	char	*buffer;

	size = 10;
	while (1)
	{
		buffer = (char *)malloc(sizeof(char) * size);
		if (!buffer)
			return (ERR);
		getcwd(buffer, size);
		if (*buffer == '/')
			break ;
		size += 10;
		free(buffer);
	}
	printf("%s\n", buffer);
	free(buffer);
	return (OK);
}
