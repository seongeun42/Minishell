/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:30:20 by sujo              #+#    #+#             */
/*   Updated: 2021/05/06 22:08:29 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_copy_1(char *dest, char const *src, size_t left, size_t right)
{
	size_t idx;

	idx = 0;
	while (left <= right)
	{
		dest[idx] = src[left];
		left++;
		idx++;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		s1_len;
	size_t		left;
	size_t		right;
	char		*result;

	if (!s1 || !set)
		return ((char *)s1);
	s1_len = ft_strlen(s1);
	if (!*s1)
		return (ft_strdup(""));
	left = 0;
	while (s1[left] && ft_strchr(set, s1[left]) != NULL)
		left++;
	if (left == s1_len)
		return (ft_strdup(""));
	right = s1_len - 1;
	while (ft_strchr(set, s1[right]) != NULL)
		right--;
	result = (char *)malloc(right - left + 2);
	if (!result)
		return (0);
	ft_str_copy_1(result, s1, left, right);
	result[right - left + 1] = '\0';
	return (result);
}
