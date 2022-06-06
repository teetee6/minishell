/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:04:33 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 22:04:34 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	clear_lexer(void)
{
	t_tok	*node;
	t_tok	*del_node;

	if (g_info.lexerbuf)
		node = g_info.lexerbuf->llisttok;
	else
		return ;
	while (node)
	{
		if (node->data)
		{
			free(node->data);
			node->data = NULL;
		}
		del_node = node;
		node = node->next;
		free(del_node);
	}
	free(g_info.lexerbuf);
	g_info.lexerbuf = NULL;
}
