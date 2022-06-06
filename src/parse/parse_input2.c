/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:22:16 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:22:16 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	type_first_letter(int c)
{
	g_info.hist_ptr->tmp = malloc((sizeof(char) * 2));
	if (!g_info.hist_ptr->tmp)
		return (-1);
	g_info.hist_ptr->tmp[0] = c;
	g_info.hist_ptr->tmp[1] = '\0';
	return (0);
}

int	type_not_less_than_two_letter(int c)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (ft_strlen(g_info.hist_ptr->tmp) + 2));
	if (!str)
		return (-1);
	i = -1;
	while (g_info.hist_ptr->tmp[++i])
		str[i] = g_info.hist_ptr->tmp[i];
	str[i] = c;
	str[i + 1] = '\0';
	free(g_info.hist_ptr->tmp);
	g_info.hist_ptr->tmp = str;
	return (0);
}
