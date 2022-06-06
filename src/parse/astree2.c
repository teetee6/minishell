/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:21:55 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:21:55 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

t_astnode	*cmd(t_tok **curtok, int *err_ch)
{
	t_astnode	*res;
	t_tok		*first;

	first = *curtok;
	res = NULL;
	while (*curtok && (*curtok)->type != CHAR_PIPE)
	{
		if (check_arrow_type(curtok))
		{
			make_arrow_node(
				&res, (*curtok)->next->data, (*curtok)->type, err_ch);
			*curtok = (*curtok)->next;
		}
		*curtok = (*curtok)->next;
	}
	*curtok = first;
	return (cmd_append_simplecmd(curtok, err_ch, res));
}

t_astnode	*simplecmd(t_tok **curtok, int *err_ch)
{
	t_astnode	*res;

	if (*err_ch)
		return (NULL);
	res = NULL;
	while (*curtok && (*curtok)->type != CHAR_PIPE)
	{
		if (check_arrow_type(curtok))
		{
			*curtok = (*curtok)->next->next;
			continue ;
		}
		make_simplecmd_node(&res, (*curtok)->data, err_ch);
		*curtok = (*curtok)->next;
	}
	return (res);
}
