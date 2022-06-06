/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:22:28 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:22:30 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	save_history(void)
{
	int			ret_fn;
	char		*ret_fn2;

	!(ret_fn = 0) && (ret_fn2 = NULL);
	check_input_empty(&ret_fn);
	if (ret_fn == RE_LOOP)
		return (ret_fn);
	check_input_all_whitespace(&ret_fn);
	if (ret_fn == RE_LOOP)
		return (ret_fn);
	ret_fn2 = ft_strdup(g_info.hist_ptr->tmp);
	if (!ret_fn2)
		return (-1);
	g_info.hist_lst->save = ret_fn2;
	clear_tmp_history();
	return (ret_fn);
}

void	check_input_empty(int *ret_fn)
{
	if (!g_info.hist_ptr->tmp || g_info.hist_ptr->tmp[0] == '\0')
	{
		cancel_current_history();
		*ret_fn = RE_LOOP;
	}
}

void	check_input_all_whitespace(int *ret_fn)
{
	int		ch;
	int		i;
	char	*str;

	ch = 0;
	i = -1;
	str = g_info.hist_ptr->tmp;
	while (str[++i])
	{
		if (str[i] != ' ')
		{
			ch = 1;
			break ;
		}
	}
	if (ch == 0)
	{
		cancel_current_history();
		*ret_fn = RE_LOOP;
	}
}

void	clear_tmp_history(void)
{
	t_history	*node;

	node = g_info.hist_lst;
	while (node)
	{
		if (node->tmp)
		{
			free(node->tmp);
			node->tmp = NULL;
		}
		node = node->next;
	}
}
