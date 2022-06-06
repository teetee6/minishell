/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewpark <jaewpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:03:50 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/03 11:30:21 by jaewpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

static int	error_unset(char *str, int *err_code)
{
	ft_putstr_fd(RED"bash: unset: `", STD_ERR);
	ft_putstr_fd(str, STD_ERR);
	ft_putstr_fd("': not a valid identifier\n"RESET, STD_ERR);
	*err_code = 1;
	return (0);
}

static int	check_char_is_valid_unset(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (-1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

int	env_delone(char *key, int *err_code)
{
	t_env	*cur;
	t_env	*prev;

	prev = g_info.env;
	cur = g_info.env;
	if (check_char_is_valid_unset(key) < 0)
		return (error_unset(key, err_code));
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			free(cur->key);
			if (cur->value)
				free(cur->value);
			if (prev != cur)
				prev->next = cur->next;
			else
				g_info.env = cur->next;
			free(cur);
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

int	ft_unset(t_cmdinfo *cmdinfo, int *err_code)
{
	int		i;

	i = 1;
	while (cmdinfo->argv[i])
	{
		env_delone(cmdinfo->argv[i], err_code);
		i++;
	}
	return (TRUE);
}
