/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:21:59 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:22:00 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	make_arrow_node(t_astnode **res, char *filename,
		t_token_type chartype, int *err_ch)
{
	t_astnode	*new;
	t_astnode	*contact;

	contact = *res;
	new = malloc(sizeof(*new));
	if (!new)
	{
		*err_ch = -1;
		return ;
	}
	set_node_for_arrow_node(new, chartype, filename, err_ch);
	if (!*res)
		*res = new;
	else
	{
		while (contact->right)
			contact = contact->right;
		ast_attach_binary_branch(contact, NULL, new);
	}
}

void	set_node_for_arrow_node(t_astnode *new, t_token_type chartype,
	char *filename, int *err_ch)
{
	new->left = NULL;
	new->right = NULL;
	if (chartype == CHAR_LESSER)
		ast_node_set_type(new, NODE_REDIRECT_IN);
	if (chartype == CHAR_GREATER)
		ast_node_set_type(new, NODE_REDIRECT_OUT);
	if (chartype == CHAR_TWO_GREATER)
		ast_node_set_type(new, NODE_REDIRECT_APPEND);
	if (chartype == CHAR_TWO_LESSER)
		ast_node_set_type(new, NODE_REDIRECT_HEREDOC);
	ast_node_set_data(new, filename, err_ch);
}

t_astnode	*cmd_append_simplecmd(t_tok **curtok, int *err_ch, t_astnode *res)
{
	t_astnode	*contact;

	if (!res)
		res = simplecmd(curtok, err_ch);
	else
	{
		contact = res;
		while (contact && contact->right)
		{
			contact = contact->right;
		}
		ast_attach_binary_branch(contact, NULL, simplecmd(curtok, err_ch));
	}
	return (res);
}

void	make_simplecmd_node(t_astnode **res, char *filename, int *err_ch)
{
	t_astnode	*new;
	t_astnode	*contact;

	contact = *res;
	new = malloc(sizeof(*new));
	new->left = NULL;
	new->right = NULL;
	ast_node_set_data(new, filename, err_ch);
	if (!*res)
	{
		new->type = NODE_CMDPATH;
		*res = new;
	}
	else
	{
		new->type = NODE_ARGUMENT;
		while (contact->right)
			contact = contact->right;
		ast_attach_binary_branch(contact, NULL, new);
	}
}
