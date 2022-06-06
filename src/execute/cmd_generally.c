/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_generally.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:19:46 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:19:47 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

static int	find_success(t_cmdinfo *cmdinfo, char *path,
	t_list **lst, char *cmdstr)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(path, "/");
	str2 = ft_strjoin(str1, cmdstr);
	if (!str1 || !str2)
	{
		if (str1)
			free(str1);
		clear_cmdinfo(cmdinfo);
		ft_lstclear(lst, free);
		exit(1);
	}
	free(str1);
	free(cmdinfo->argv[0]);
	cmdinfo->argv[0] = str2;
	return (TRUE);
}

void	parse_path(t_list **lst, t_cmdinfo *cmdinfo)
{
	char	**path;
	char	*str;
	int		i;

	*lst = NULL;
	str = env_search("PATH");
	if (!ft_strcmp(str, ""))
	{
		free(str);
		return ;
	}
	path = ft_split(str, ':');
	if (!path)
	{
		free(str);
		clear_cmdinfo(cmdinfo);
		exit (1);
	}
	free(str);
	i = -1;
	while (path[++i])
		ft_lstadd_front(lst, ft_lstnew(path[i]));
	free(path);
}

int	find_cmd_generally2(t_cmdinfo *cmdinfo, t_list *path,
	char *cmdstr, t_list **save)
{
	DIR				*dirp;
	struct dirent	*r;

	dirp = opendir((char *)path->content);
	while (dirp)
	{
		r = readdir(dirp);
		if (!r)
			break ;
		else if (!ft_strcmp(r->d_name, ".") || !ft_strcmp(r->d_name, ".."))
			continue ;
		else if (!ft_strcmp(cmdstr, r->d_name))
		{
			find_success(cmdinfo, path->content, save, cmdstr);
			closedir(dirp);
			ft_lstclear(save, free);
			return (TRUE);
		}
	}
	closedir(dirp);
	return (FALSE);
}

int	find_cmd_generally(t_cmdinfo *cmdinfo)
{
	t_list			*path;
	t_list			*save;
	char			*cmdstr;
	int				ret_code;

	parse_path(&path, cmdinfo);
	if (!path)
		return (0);
	save = path;
	cmdstr = cmdinfo->argv[0];
	while (path)
	{
		ret_code = find_cmd_generally2(cmdinfo, path, cmdstr, &save);
		if (ret_code == -1)
			break ;
		if (ret_code == TRUE)
			return (TRUE);
		path = path->next;
	}
	ft_lstclear(&save, free);
	return (FALSE);
}
