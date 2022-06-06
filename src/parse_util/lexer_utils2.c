/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:24:27 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:24:28 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	count_list(void)
{
	t_tok	*token;
	int		i;

	i = 0;
	token = g_info.lexerbuf->llisttok;
	while (token)
	{
		i++;
		token = token->next;
	}
	g_info.lexerbuf->ntoks = i;
}

void	delete_trash(t_tok **token)
{
	t_tok	*cur_node;
	t_tok	*del_node;

	delete_trash_front_loop(token);
	cur_node = *token;
	if (!cur_node)
		return ;
	while (cur_node)
	{
		if (!cur_node->data || !ft_strcmp(cur_node->data, ""))
		{
			del_node = cur_node;
			if (cur_node->data && !ft_strcmp(cur_node->data, ""))
				free(del_node->data);
			if (cur_node->prev)
				cur_node->prev->next = cur_node->next;
			if (cur_node->next)
				cur_node->next->prev = cur_node->prev;
			cur_node = cur_node->next;
			free(del_node);
			continue ;
		}
		cur_node = cur_node->next;
	}
}

void	delete_trash_front_loop(t_tok **token)
{
	t_tok	*cur_node;
	t_tok	*del_node;

	cur_node = *token;
	while (cur_node && (!cur_node->data || !ft_strcmp(cur_node->data, "")))
	{
		del_node = cur_node;
		if (cur_node->data && !ft_strcmp(cur_node->data, ""))
			free(del_node->data);
		cur_node = cur_node->next;
		free(del_node);
	}
	*token = cur_node;
}
