/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 07:25:37 by hyoslee           #+#    #+#             */
/*   Updated: 2021/05/07 14:21:29 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	is_included_in(char target, char *str)
{
	while (*str)
	{
		if (*str == target)
			return (1);
		str++;
	}
	return (0);
}

static int	is_number(char chr)
{
	return (chr >= '0' && chr <= '9');
}

int	ft_atoi(const char *str)
{
	long		result;
	long		sign;

	sign = 1;
	result = 0;
	while (is_included_in(*str, " \t\n\v\f\r"))
		str++;
	if (is_included_in(*str, "+-"))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (is_number(*str))
	{
		result = result * 10 + *str - '0';
		if (result > 2147483647 && sign == 1)
			return (-1);
		if (result > 2147483648 && sign == -1)
			return (0);
		str++;
	}
	return (result * sign);
}
