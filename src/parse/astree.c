/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:03:47 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 22:03:48 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	astree(void)
{
	int		err_ch;
	t_tok	*save;

	err_ch = 0;
	save = g_info.lexerbuf->llisttok;
	g_info.astnode = job(&save, &err_ch);
	return (err_ch);
}

t_astnode	*job(t_tok **curtok, int *err_ch)
{
	t_tok		*save;
	t_astnode	*node;

	save = *curtok;
	if (*err_ch)
		return (NULL);
	node = NULL;
	*curtok = save;
	node = job1(curtok, err_ch);
	if (*err_ch || node)
		return (node);
	*curtok = save;
	node = job2(curtok, err_ch);
	if (*err_ch || node)
		return (node);
	return (NULL);
}

t_astnode	*job1(t_tok **curtok, int *err_ch)
{
	t_astnode	*cmd_node;
	t_astnode	*job_node;
	t_astnode	*result;

	cmd_node = cmd(curtok, err_ch);
	if (*err_ch || cmd_node == NULL)
		return (NULL);
	if (!assert_type(CHAR_PIPE, NULL, curtok, err_ch))
	{
		ast_node_delete(cmd_node);
		return (NULL);
	}
	job_node = job(curtok, err_ch);
	if (*err_ch || job_node == NULL)
	{
		ast_node_delete(cmd_node);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	if (!result)
		*err_ch = -1;
	ast_node_set_type(result, NODE_PIPE);
	ast_node_set_data(result, "|", err_ch);
	ast_attach_binary_branch(result, cmd_node, job_node);
	return (result);
}

t_astnode	*job2(t_tok **curtok, int *err_ch)
{
	return (cmd(curtok, err_ch));
}
