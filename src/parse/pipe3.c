/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:22:25 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:22:26 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	init_cmdinfo(t_astnode *simple_cmd_node, t_cmdinfo *cmdinfo)
{
	t_astnode	*arg_node;
	int			i;

	if (simple_cmd_node == NULL || !(simple_cmd_node->type == NODE_CMDPATH))
	{
		cmdinfo->argc = 0;
		return (-1);
	}
	arg_node = simple_cmd_node;
	i = 0;
	while (arg_node != NULL
		&& (arg_node->type == NODE_ARGUMENT || arg_node->type == NODE_CMDPATH))
	{
		arg_node = arg_node->right;
		i++;
	}
	cmdinfo->argv = (char **)malloc(sizeof(char *) * (i + 1));
	arg_node = simple_cmd_node;
	init_cmdinfo2(arg_node, cmdinfo);
	return (0);
}

int	init_cmdinfo2(t_astnode *arg_node, t_cmdinfo *cmdinfo)
{
	int	i;

	i = 0;
	while (arg_node != NULL
		&& (arg_node->type == NODE_ARGUMENT || arg_node->type == NODE_CMDPATH))
	{
		cmdinfo->argv[i] = ft_strdup(arg_node->data);
		arg_node = arg_node->right;
		i++;
	}
	cmdinfo->argv[i] = NULL;
	cmdinfo->argc = i;
	return (0);
}

void	set_cmdinfo(t_astnode *cmdnode, t_pipeinfo pipeinfo, t_cmdinfo *cmdinfo,
		int *err_code)
{
	t_list		*redir_outfd;
	int			has_redir_in_heredoc;

	has_redir_in_heredoc = FALSE;
	cmdinfo->pipeinfo = pipeinfo;
	!(cmdinfo->argc = 0) && (cmdinfo->argv = 0);
	!(cmdinfo->redir_in = 0) && (cmdinfo->redir_out = 0);
	pipe(cmdinfo->redir_pipe);
	handle_redir(cmdnode, cmdinfo, &has_redir_in_heredoc, err_code);
	close(cmdinfo->redir_pipe[1]);
	if (*err_code != 0)
		return ;
	if (has_redir_in_heredoc)
		cmdinfo->redir_in = cmdinfo->redir_pipe[0];
	while (cmdnode && cmdnode->type != NODE_CMDPATH)
		cmdnode = cmdnode->right;
	init_cmdinfo(cmdnode, cmdinfo);
	redir_outfd = ft_lstlast(g_info.outfd_lst);
	if (redir_outfd)
		cmdinfo->redir_out = ft_atoi(redir_outfd->content);
}

void	clear_cmdinfo(t_cmdinfo *cmdinfo)
{
	t_list	*redir_outfd;

	redir_outfd = g_info.outfd_lst;
	while (redir_outfd)
	{
		close(ft_atoi(redir_outfd->content));
		redir_outfd = redir_outfd->next;
	}
	close(cmdinfo->redir_pipe[0]);
	ft_lstclear(&g_info.outfd_lst, free);
	destroy_cmdinfo(cmdinfo);
}

void	destroy_cmdinfo(t_cmdinfo *cmdinfo)
{
	int	i;

	if (cmdinfo->argv == NULL)
		return ;
	i = -1;
	while (++i < cmdinfo->argc)
	{
		if (cmdinfo->argv[i])
			free(cmdinfo->argv[i]);
	}
	free(cmdinfo->argv);
	cmdinfo->argc = 0;
}
