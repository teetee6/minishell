/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 00:39:26 by hyoslee           #+#    #+#             */
/*   Updated: 2021/05/07 07:17:31 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l_len;
	size_t	b_len;
	size_t	size;

	if (*little == '\0')
		return ((char *)big);
	l_len = ft_strlen(little);
	b_len = ft_strlen(big);
	if (b_len < l_len || len < l_len)
		return (0);
	size = b_len;
	if (b_len > len)
		size = len;
	while (size-- >= l_len)
	{
		if (ft_memcmp(big, little, l_len) == 0)
			return ((char *)big);
		big++;
	}
	return (0);
}
