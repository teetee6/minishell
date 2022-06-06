/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_directly.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:19:43 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:19:44 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	find_cmd_directly(t_cmdinfo *cmdinfo, int *type)
{
	struct stat	buf;

	if (stat(cmdinfo->argv[0], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			*type = IS_DIR;
			return (0);
		}
		else
			return (1);
	}
	else
	{
		*type = NSFD;
		return (0);
	}
	return (0);
}
