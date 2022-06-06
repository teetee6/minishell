/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewpark <jaewpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:03:50 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/03 11:28:57 by jaewpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	builtin(t_cmdinfo *cmdinfo, int *err_code)
{
	if (!ft_strcmp("echo", cmdinfo->argv[0]))
		return (ft_echo(cmdinfo));
	if (!ft_strcmp("cd", cmdinfo->argv[0]))
		return (ft_cd(cmdinfo, err_code));
	if (!ft_strcmp("pwd", cmdinfo->argv[0]))
		return (ft_pwd());
	if (!ft_strcmp("export", cmdinfo->argv[0]))
		return (ft_export(cmdinfo, err_code));
	if (!ft_strcmp("unset", cmdinfo->argv[0]))
		return (ft_unset(cmdinfo, err_code));
	if (!ft_strcmp("env", cmdinfo->argv[0]))
		return (ft_env());
	if (!ft_strcmp("exit", cmdinfo->argv[0]))
		return (ft_exit(cmdinfo, err_code));
	return (FALSE);
}

void	execute_simple_command(t_cmdinfo *cmdinfo, int *err_code)
{
	int	type;

	if (cmdinfo->argc <= 0)
		return ;
	modify_stdin_stdout(cmdinfo);
	if (builtin(cmdinfo, err_code))
		;
	else if (!ft_strncmp("./", cmdinfo->argv[0], 2)
		|| !ft_strncmp("../", cmdinfo->argv[0], 3)
		|| cmdinfo->argv[0][0] == '/')
	{
		if (find_cmd_directly(cmdinfo, &type))
			path_execute(cmdinfo, err_code);
		else
			execute_error(cmdinfo->argv[0], type, err_code);
	}
	else if (find_cmd_generally(cmdinfo))
		path_execute(cmdinfo, err_code);
	else
		execute_error(cmdinfo->argv[0], NOTF, err_code);
	reset_stdin_stdout();
	return ;
}

static void	path_execute_child(t_cmdinfo *cmdinfo, int *err_code)
{
	char		**envp;

	envp = make_envp();
	if (execve(cmdinfo->argv[0], cmdinfo->argv, envp) < 0)
	{
		free_str(envp);
		execute_error(cmdinfo->argv[0], 1, err_code);
		exit(127);
	}
	free_str(envp);
	exit(0);
}

void	path_execute(t_cmdinfo *cmdinfo, int *err_code)
{
	pid_t		pid;
	int			status;

	if (!ft_strcmp(cmdinfo->argv[0], "/bin/cat")
		|| !ft_strcmp(cmdinfo->argv[0], "/usr/bin/wc"))
		g_info.is_in_cat_wc = TRUE;
	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
		path_execute_child(cmdinfo, err_code);
	else
	{
		wait_until_child_closed(pid, &status, err_code);
		*err_code = g_info.is_in_cat_wc;
		g_info.is_in_cat_wc = FALSE;
	}
}

void	execute_error(char *cmd, int type, int *err_code)
{
	ft_putstr_fd(RED"bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": "RESET, 2);
	if (type == 1)
	{
		ft_putendl_fd(strerror(errno), 2);
		*err_code = 127;
	}
	else if (type == IS_DIR)
	{
		if (type == IS_DIR)
			ft_putendl_fd(RED"is a directory"RESET, 2);
		*err_code = 126;
	}
	else if (type == NSFD || type == NOTF)
	{
		*err_code = 127;
		if (type == NOTF)
			ft_putendl_fd(RED"command not found"RESET, STD_ERR);
		else if (type == NSFD)
			ft_putendl_fd(RED"No such file or directory"RESET, STD_ERR);
	}
}
