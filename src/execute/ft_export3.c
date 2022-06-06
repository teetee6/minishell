/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:20:14 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:20:15 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	env_add(t_env **lst, t_env *new)
{
	t_env	*cur;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	print_export(void)
{
	t_env	*tmp;

	tmp = g_info.env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "?"))
		{
			tmp = tmp->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putendl_fd("", 1);
		tmp = tmp->next;
	}
}

void	error_export(char *str, int *err_code)
{
	ft_putstr_fd(RED"bash: export: `", STD_ERR);
	ft_putstr_fd(str, STD_ERR);
	ft_putstr_fd("': not a valid identifier\n"RESET, STD_ERR);
	*err_code = EXPORT_NOT_VALID;
}
