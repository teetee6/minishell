/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewpark <jaewpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:04:14 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 16:41:42 by jaewpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	handle_redir(t_astnode *cmdnode, t_cmdinfo *cmdinfo,
	int *has_redir_in_heredoc, int *err_code)
{
	while (cmdnode && cmdnode->type != NODE_CMDPATH)
	{
		if (*err_code != 0)
			break ;
		if (cmdnode->type == NODE_REDIRECT_IN)
		{
			handle_redir_in(cmdnode, cmdinfo, err_code);
			*has_redir_in_heredoc = TRUE;
		}
		else if (cmdnode->type == NODE_REDIRECT_HEREDOC)
		{
			handle_redir_heredoc_wrapper(cmdnode, cmdinfo, err_code);
			if (*err_code != 0)
				break ;
			*has_redir_in_heredoc = TRUE;
		}
		handle_redir_out_append(cmdnode);
		cmdnode = cmdnode->right;
	}
}

void	handle_redir_in(t_astnode *cmdnode, t_cmdinfo *cmdinfo, int *err_code)
{
	int	fd;

	fd = open(cmdnode->data, O_RDONLY);
	if (fd == -1)
		*err_code = ERROR_NSFD;
	else
		write_gnl(fd, cmdinfo->redir_pipe[1]);
	close(fd);
}

void	handle_redir_heredoc_wrapper(t_astnode *cmdnode, t_cmdinfo *cmdinfo,
int *err_code)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		g_info.is_in_here = TRUE;
		handle_redir_heredoc(cmdnode, cmdinfo);
		close(cmdinfo->redir_pipe[1]);
		close(cmdinfo->redir_pipe[0]);
		exit(0);
	}
	else
	{
		wait_until_child_closed(pid, &status, err_code);
		if (*err_code == 1)
			*err_code = SIGINT_HEREDOC;
		g_info.is_in_here = FALSE;
	}
}

void	handle_redir_heredoc(t_astnode *cmdnode, t_cmdinfo *cmdinfo)
{
	char	*line;
	char	*eof;
	t_list	*here_str_lst;

	eof = cmdnode->data;
	here_str_lst = g_info.here_str_lst;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, eof))
		{
			free(line);
			while (here_str_lst)
			{
				ft_putendl_fd(here_str_lst->content, cmdinfo->redir_pipe[1]);
				here_str_lst = here_str_lst->next;
			}
			break ;
		}
		find_env_and_replace(&line);
		ft_lstadd_back(&here_str_lst, ft_lstnew(line));
	}
	ft_lstclear(&g_info.here_str_lst, free);
}

void	handle_redir_out_append(t_astnode *cmdnode)
{
	int	out_fd;

	if (cmdnode->type == NODE_REDIRECT_OUT)
	{
		out_fd = open(cmdnode->data, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		ft_lstadd_back(&g_info.outfd_lst, ft_lstnew(ft_itoa(out_fd)));
	}
	else if (cmdnode->type == NODE_REDIRECT_APPEND)
	{
		out_fd = open(cmdnode->data, O_WRONLY | O_APPEND | O_CREAT, 0644);
		ft_lstadd_back(&g_info.outfd_lst, ft_lstnew(ft_itoa(out_fd)));
	}
}
