/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:24:41 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:24:41 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	__init_write_open(t_pipeinfo *pipeinfo, int *psuedo_pipe)
{
	pipe(psuedo_pipe);
	pipeinfo->cmd_pipe[0] = psuedo_pipe[0];
	pipeinfo->cmd_pipe[1] = psuedo_pipe[1];
	pipeinfo->has_in_pipe = FALSE;
	pipeinfo->has_out_pipe = TRUE;
}

void	__prev_write_close__cur_write_open(t_pipeinfo *pipeinfo,
										int *psuedo_pipe)
{
	close(pipeinfo->cmd_pipe[1]);
	pipe(psuedo_pipe);
	pipeinfo->cmd_pipe[1] = psuedo_pipe[1];
	pipeinfo->has_in_pipe = TRUE;
}

void	__cur_read_close__next_read_open(t_pipeinfo *pipeinfo, int *psuedo_pipe)
{
	close(pipeinfo->cmd_pipe[0]);
	pipeinfo->cmd_pipe[0] = psuedo_pipe[0];
}

void	__prev_write_close(t_pipeinfo *pipeinfo, int *psuedo_pipe)
{
	pipeinfo->cmd_pipe[0] = psuedo_pipe[0];
	close(pipeinfo->cmd_pipe[1]);
	pipeinfo->has_out_pipe = FALSE;
	pipeinfo->has_in_pipe = TRUE;
}

void	__final_read_close(t_pipeinfo *pipeinfo)
{
	close(pipeinfo->cmd_pipe[0]);
}
