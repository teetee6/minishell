/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:22:22 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:22:23 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	close_all_pipe(t_pipeinfo *pipeinfo, int *pseudo_pipe)
{
	if (pipeinfo->cmd_pipe[0])
		close(pipeinfo->cmd_pipe[0]);
	if (pipeinfo->cmd_pipe[1])
		close(pipeinfo->cmd_pipe[1]);
	if (pseudo_pipe[0])
		close(pseudo_pipe[0]);
	if (pseudo_pipe[1])
		close(pseudo_pipe[1]);
}

void	has_multiple_pipelines(t_astnode **jobnode2, t_pipeinfo *pipeinfo,
	int *psuedo_pipe, int *ret_code)
{
	while (*jobnode2 != NULL && (*jobnode2)->type == NODE_PIPE)
	{
		__prev_write_close__cur_write_open(pipeinfo, psuedo_pipe);
		*ret_code = execute_command_pipe_wrapper((*jobnode2)->left, *pipeinfo);
		if (*ret_code == SIGINT_HEREDOC || *ret_code == 130 || *ret_code == 131)
		{
			close_all_pipe(pipeinfo, psuedo_pipe);
			return ;
		}
		g_info.ret = 0;
		__cur_read_close__next_read_open(pipeinfo, psuedo_pipe);
		*jobnode2 = (*jobnode2)->right;
	}
}
