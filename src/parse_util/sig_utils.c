/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewpark <jaewpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:04:37 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 16:47:19 by jaewpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

static void	sig_int2(void)
{
	if (g_info.hist_ptr->tmp)
	{
		free(g_info.hist_ptr->tmp);
		g_info.hist_ptr->tmp = NULL;
	}
	write(STD_OUT, "\nminishell$ ", 13);
	g_info.ret = 1;
}

static void	sig_int(void)
{
	if (g_info.astnode)
	{
		if (g_info.is_in_here == TRUE)
		{
			ft_putstr_fd("\b\b  \b\b\n", STD_OUT);
			exit(1);
		}
		else
		{
			if (g_info.is_in_cat_wc)
			{
				g_info.is_in_cat_wc = 130;
				ft_putendl_fd("", 1);
			}
		}
	}
	else
		sig_int2();
}

static void	sig_quit(void)
{
	if (g_info.astnode && g_info.is_in_cat_wc == TRUE)
	{
		g_info.is_in_cat_wc = 131;
		ft_putendl_fd("Quit: 3", 1);
	}
}

void	handler(int signo)
{
	if (signo == SIGINT)
		sig_int();
	else if (signo == SIGQUIT)
		sig_quit();
}
