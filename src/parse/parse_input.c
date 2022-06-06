/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:04:03 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 22:04:04 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	handle_input(void)
{
	int	c;
	int	ret_fn;

	if (create_history() == -1)
		return (-1);
	!(c = 0) && (ret_fn = 0);
	while (read(STD_IN, &c, sizeof(c)))
	{
		if (c == '\n')
		{
			ft_putchar_fd('\n', STD_OUT);
			break ;
		}
		else
		{
			ret_fn = handle_key(c);
			if (ret_fn != 0)
				return (ret_fn);
		}
		c = 0;
	}
	ret_fn = save_history();
	if (ret_fn != 0)
		return (ret_fn);
	return (0);
}

int	handle_key(int c)
{
	int	err_ret;

	err_ret = 0;
	if (c == KEY_EOF)
		return (handle_key_eof());
	else if (c == KEY_BSPACE)
		err_ret = del_last_char();
	else if (c == KEY_ARROW_UP)
		err_ret = history_up();
	else if (c == KEY_ARROW_DOWN)
		err_ret = history_down();
	else if (ft_isprint((char)c))
		err_ret = save_key(c);
	if (err_ret == -1)
		return (-1);
	return (0);
}

int	handle_key_eof(void)
{
	if (!(g_info.hist_ptr->tmp) || g_info.hist_ptr->tmp[0] == '\0')
	{
		if (g_info.hist_ptr->tmp)
		{
			free(g_info.hist_ptr->tmp);
			g_info.hist_ptr->tmp = NULL;
		}
		ft_putstr_fd("exit\n", STD_OUT);
	}
	else
		ft_putstr_fd("\nexit\n", STD_OUT);
	return (KEY_EOF);
}

int	save_key(int c)
{
	if (!(g_info.hist_ptr->tmp))
	{
		if (type_first_letter(c) == -1)
			return (-1);
	}
	else
	{
		if (type_not_less_than_two_letter(c) == -1)
			return (-1);
	}
	ft_putchar_fd(c, STD_OUT);
	return (0);
}

int	del_last_char(void)
{
	int		len;
	char	*str;

	if (!(g_info.hist_ptr->tmp) || g_info.hist_ptr->tmp[0] == '\0')
		return (0);
	else
	{
		len = ft_strlen(g_info.hist_ptr->tmp);
		ft_putstr_fd("\b \b", STD_OUT);
		str = malloc(sizeof(char) * len);
		if (!str)
			return (-1);
		ft_strlcpy(str, g_info.hist_ptr->tmp, len);
		free(g_info.hist_ptr->tmp);
		g_info.hist_ptr->tmp = str;
		return (0);
	}
}
