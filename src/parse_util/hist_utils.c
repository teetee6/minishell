/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:04:31 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 22:04:31 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

t_history	*ft_histnew(char *save)
{
	t_history	*new;

	new = malloc(sizeof(t_history));
	if (!new)
		return (NULL);
	new->save = save;
	new->tmp = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_histadd_front(t_history **lst, t_history *new)
{
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	new->next = *lst;
	(*lst)->prev = new;
	*lst = new;
}

void	clear_history(void)
{
	t_history	*node;
	t_history	*del_node;

	node = g_info.hist_lst;
	while (node)
	{
		if (node->tmp)
		{
			free(node->tmp);
			node->tmp = NULL;
		}
		if (node->save)
		{
			free(node->save);
			node->save = NULL;
		}
		del_node = node;
		node = node->next;
		free(del_node);
	}
	g_info.hist_lst = NULL;
}
