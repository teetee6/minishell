/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:03:50 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/01 10:12:24 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

static int	check_if_need_newline(char **argv, int *need_newline)
{
	int		i;
	int		j;

	*need_newline = TRUE;
	i = 1;
	if (ft_strncmp(argv[i], "-n", 2) != 0)
		return (i);
	while (argv[i] && !ft_strncmp(argv[i], "-n", 2))
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] != 'n')
				return (i);
			j++;
		}
		*need_newline = FALSE;
		i++;
	}
	return (i);
}

int	ft_echo(t_cmdinfo *cmdinfo)
{
	int	need_newline;
	int	i;

	if (cmdinfo->argc <= 1)
	{
		write(1, "\n", 1);
		return (TRUE);
	}
	i = check_if_need_newline(cmdinfo->argv, &need_newline);
	if (i < cmdinfo->argc)
		ft_putstr_fd(cmdinfo->argv[i++], 1);
	while (i < cmdinfo->argc)
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(cmdinfo->argv[i], 1);
		i++;
	}
	if (need_newline == TRUE)
		ft_putendl_fd("", 1);
	return (TRUE);
}
