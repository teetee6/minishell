/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewpark <jaewpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:03:50 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 16:50:58 by jaewpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	execute(void)
{
	t_pipeinfo	pipeinfo;
	int			ret_code;

	!(pipeinfo.has_in_pipe = 0) && (pipeinfo.has_out_pipe = 0);
	!(pipeinfo.cmd_pipe[0] = 0) && (pipeinfo.cmd_pipe[1] = 0);
	ret_code = 0;
	if (g_info.astnode->type == NODE_PIPE)
		ret_code = execute_pipeline(g_info.astnode);
	else
		ret_code = execute_command(g_info.astnode, pipeinfo);
	g_info.ret = ret_code;
	if (ret_code == SIGINT_HEREDOC || ret_code == ERROR_NSFD
		|| ret_code == CD_HOME_NOTSET || ret_code == CD_NSFD
		|| ret_code == EXPORT_NOT_VALID || ret_code == EXIT_TOO_MANY_ARGS)
		g_info.ret = 1;
}

int	execute_pipeline(t_astnode *jobnode1)
{
	t_pipeinfo	pipeinfo;
	t_astnode	*jobnode2;
	int			psuedo_pipe[2];
	int			ret_code;

	ret_code = 0;
	__init_write_open(&pipeinfo, psuedo_pipe);
	ret_code = execute_command_pipe_wrapper(jobnode1->left, pipeinfo);
	if (ret_code == SIGINT_HEREDOC || ret_code == 130 || ret_code == 131)
	{
		close_all_pipe(&pipeinfo, psuedo_pipe);
		return (ret_code);
	}
	g_info.ret = 0;
	jobnode2 = jobnode1->right;
	has_multiple_pipelines(&jobnode2, &pipeinfo, psuedo_pipe, &ret_code);
	if (ret_code == SIGINT_HEREDOC || ret_code == 130 || ret_code == 131)
		return (ret_code);
	__prev_write_close(&pipeinfo, psuedo_pipe);
	ret_code = execute_command_pipe_wrapper(jobnode2, pipeinfo);
	__final_read_close(&pipeinfo);
	return (ret_code);
}

static void	handle_err_code(t_astnode *cmdnode, int *err_code)
{
	if (*err_code == ERROR_NSFD)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(cmdnode->data, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		ft_putstr_fd(RESET, 1);
	}
}

int	execute_command(t_astnode *cmdnode, t_pipeinfo pipeinfo)
{
	t_cmdinfo	cmdinfo;
	int			err_code;

	if (cmdnode == NULL)
		return (0);
	err_code = 0;
	set_cmdinfo(cmdnode, pipeinfo, &cmdinfo, &err_code);
	if (err_code == 0)
		execute_simple_command(&cmdinfo, &err_code);
	if (err_code)
		handle_err_code(cmdnode, &err_code);
	clear_cmdinfo(&cmdinfo);
	return (err_code);
}

int	execute_command_pipe_wrapper(t_astnode *cmdnode, t_pipeinfo pipeinfo)
{
	pid_t	pid;
	int		status;
	int		err_code;

	err_code = 0;
	pid = fork();
	if (pid == 0)
	{
		err_code = execute_command(cmdnode, pipeinfo);
		exit(err_code);
	}
	else
		wait_until_child_closed(pid, &status, &err_code);
	return (err_code);
}
