/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:12:44 by sujo              #+#    #+#             */
/*   Updated: 2021/05/06 21:57:15 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	idx;
	size_t	str_len;

	if (!s)
		return (0);
	str_len = ft_strlen(s);
	if (str_len < start)
		return (ft_strdup(""));
	if (str_len < start + len)
		len = str_len - start;
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	idx = 0;
	while (idx < len && s[idx + start] != '\0')
	{
		result[idx] = s[idx + start];
		idx++;
	}
	result[idx] = '\0';
	return (result);
}
