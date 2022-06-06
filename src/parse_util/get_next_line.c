/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 05:32:26 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 22:04:18 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_newline(char *backup)
{
	int	i;

	i = 0;
	while (backup[i])
	{
		if (backup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	split_line(char **backup, char **line, int cut_idx)
{
	char			*temp;
	int				next_str_len;

	(*backup)[cut_idx] = '\0';
	*line = ft_strdup(*backup);
	next_str_len = ft_strlen(*backup + cut_idx + 1);
	if (next_str_len == 0)
	{
		free(*backup);
		*backup = 0;
		return (1);
	}
	temp = ft_strdup(*backup + cut_idx + 1);
	free(*backup);
	*backup = temp;
	return (1);
}

int	return_all(char **backup, char **line)
{
	int				cut_idx;

	if (*backup)
	{
		cut_idx = has_newline(*backup);
		if (cut_idx >= 0)
			return (split_line(backup, line, cut_idx));
	}
	else if (*backup)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char		*backup[32];
	char			buf[5001];
	int				read_size;
	int				cut_idx;

	if ((!line) || (fd < 0))
		return (-1);
	read_size = read(fd, buf, 5000);
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buf);
		cut_idx = has_newline(backup[fd]);
		if (cut_idx >= 0)
			return (split_line(&backup[fd], line, cut_idx));
		read_size = read(fd, buf, 5000);
	}
	if (read_size < 0)
		return (-1);
	return (return_all(&backup[fd], line));
}
