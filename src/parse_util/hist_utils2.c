/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:24:23 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:24:24 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	create_history(void)
{
	g_info.hist_ptr = ft_histnew(NULL);
	if (g_info.hist_ptr == NULL)
		return (-1);
	ft_histadd_front(&g_info.hist_lst, g_info.hist_ptr);
	return (0);
}

int	history_up(void)
{
	int		ptrlen;
	char	*ret_fn;

	ret_fn = NULL;
	if (!g_info.hist_ptr || !(g_info.hist_ptr->next))
		return (0);
	if (g_info.hist_ptr->tmp)
	{
		ptrlen = ft_strlen(g_info.hist_ptr->tmp);
		while (ptrlen--)
			ft_putstr_fd("\b \b", STD_OUT);
	}
	g_info.hist_ptr = g_info.hist_ptr->next;
	if (!(g_info.hist_ptr->tmp))
	{
		ret_fn = ft_strdup(g_info.hist_ptr->save);
		if (!ret_fn)
			return (-1);
		g_info.hist_ptr->tmp = ret_fn;
	}
	ft_putstr_fd(g_info.hist_ptr->tmp, STD_OUT);
	return (0);
}

int	history_down(void)
{
	int		ptrlen;

	if (!g_info.hist_ptr || !(g_info.hist_ptr->prev))
		return (0);
	if (g_info.hist_ptr->tmp)
	{
		ptrlen = ft_strlen(g_info.hist_ptr->tmp);
		while (ptrlen--)
			ft_putstr_fd("\b \b", STD_OUT);
	}
	g_info.hist_ptr = g_info.hist_ptr->prev;
	ft_putstr_fd(g_info.hist_ptr->tmp, STD_OUT);
	return (0);
}

void	cancel_current_history(void)
{
	t_history	*del_hist;

	del_hist = g_info.hist_lst;
	g_info.hist_lst = g_info.hist_lst->next;
	if (del_hist->tmp)
		free(del_hist->tmp);
	free(del_hist);
	clear_tmp_history();
}
