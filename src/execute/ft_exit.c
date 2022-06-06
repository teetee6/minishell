/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewpark <jaewpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:03:50 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 16:58:50 by jaewpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	print_exit_error(char *str, int code)
{
	if (code == 1)
	{
		ft_putstr_fd("bash: exit: ", STD_ERR);
		ft_putstr_fd(str, STD_ERR);
		ft_putstr_fd(": numeric argument required\n", STD_ERR);
		g_info.ret = 255;
	}
	else
		ft_putstr_fd(str, STD_ERR);
	return (1);
}

int	ft_exit(t_cmdinfo *cmdinfo, int *err_code)
{
	reset_stdin_stdout();
	if (!(cmdinfo->pipeinfo.has_out_pipe || cmdinfo->pipeinfo.has_in_pipe))
		ft_putendl_fd("exit", 1);
	if (cmdinfo->argc > 1)
	{
		if (is_num(cmdinfo->argv[1]) == FALSE)
		{
			ft_putstr_fd(RED"bash: exit: ", STD_ERR);
			ft_putstr_fd(cmdinfo->argv[1], STD_ERR);
			ft_putendl_fd(": numeric argument required"RESET, STD_ERR);
			g_info.ret = 255;
			exit(g_info.ret);
		}
		else if (cmdinfo->argc == 2)
			exit(ft_atoi(cmdinfo->argv[1]));
		if (cmdinfo->argc > 2)
		{
			*err_code = EXIT_TOO_MANY_ARGS;
			ft_putendl_fd(RED"bash: exit: too many arguments"RESET, STD_ERR);
			return (TRUE);
		}
	}
	exit(g_info.ret);
	return (TRUE);
}
