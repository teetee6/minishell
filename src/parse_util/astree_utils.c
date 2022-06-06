/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:04:10 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 22:04:10 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	ast_attach_binary_branch(t_astnode *root,
	t_astnode *leftNode, t_astnode *rightNode)
{
	if (root == NULL)
		return ;
	root->left = leftNode;
	root->right = rightNode;
}

void	ast_node_set_type(t_astnode *node, t_node_type nodetype)
{
	if (node == NULL)
		return ;
	node->type = nodetype;
}

void	ast_node_set_data(t_astnode *node, char *data, int *err_ch)
{
	if (node == NULL)
		return ;
	node->data = ft_strdup(data);
	if (!node->data)
		*err_ch = -1;
}

void	ast_node_delete(t_astnode *node)
{
	if (node == NULL)
		return ;
	ast_node_delete(node->left);
	ast_node_delete(node->right);
	if (node->data)
		free(node->data);
	free(node);
}

int	assert_type(int toketype, char **bufferptr, t_tok **curtok, int *err_ch)
{
	if (*curtok == NULL)
		return (FALSE);
	if ((*curtok)->type == toketype)
	{
		if (bufferptr != NULL)
		{
			*bufferptr = ft_strdup((*curtok)->data);
			if (!*bufferptr)
				*err_ch = -1;
		}
		*curtok = (*curtok)->next;
		return (TRUE);
	}
	return (FALSE);
}
