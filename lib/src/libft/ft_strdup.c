/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 07:53:05 by hyoslee           #+#    #+#             */
/*   Updated: 2021/05/07 08:09:33 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *src)
{
	char	*result;
	int		i;

	result = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (result == NULL)
		return (NULL);
	i = -1;
	while (src[++i])
		result[i] = src[i];
	result[i] = '\0';
	return (result);
}
