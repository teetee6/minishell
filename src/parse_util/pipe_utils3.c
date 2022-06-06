/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewpark <jaewpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:04:14 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 16:42:30 by jaewpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	wait_until_child_closed(int pid, int *status, int *save)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
	{
		if (save == NULL)
			return ;
		*save = WEXITSTATUS(*status);
	}
}

void	modify_stdin_stdout(t_cmdinfo *cmdinfo)
{
	g_info.stdin_fd = dup(STDIN_FILENO);
	g_info.stdout_fd = dup(STDOUT_FILENO);
	if (cmdinfo->pipeinfo.has_in_pipe)
		dup2(cmdinfo->pipeinfo.cmd_pipe[0], STDIN_FILENO);
	if (cmdinfo->redir_in)
		dup2(cmdinfo->redir_in, STDIN_FILENO);
	if (cmdinfo->pipeinfo.has_out_pipe)
		dup2(cmdinfo->pipeinfo.cmd_pipe[1], STDOUT_FILENO);
	if (cmdinfo->redir_out)
		dup2(cmdinfo->redir_out, STDOUT_FILENO);
}

void	reset_stdin_stdout(void)
{
	dup2(g_info.stdin_fd, STDIN_FILENO);
	dup2(g_info.stdout_fd, STDOUT_FILENO);
}
