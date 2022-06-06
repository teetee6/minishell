/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 05:32:26 by hyoslee           #+#    #+#             */
/*   Updated: 2021/05/11 17:45:43 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	write_gnl(int file_fd, int write_fd)
{
	char	*line;
	int		ret;

	while (1)
	{
		ret = get_next_line(file_fd, &line);
		if (ret > 0)
		{
			write(write_fd, line, ft_strlen(line));
			write(write_fd, "\n", 1);
			free(line);
		}
		else if (ret == 0)
		{
			if (!ft_strcmp("", line))
			{
				free(line);
				break ;
			}
			write(write_fd, line, ft_strlen(line));
			write(write_fd, "\n", 1);
			free(line);
			break ;
		}
	}
}
