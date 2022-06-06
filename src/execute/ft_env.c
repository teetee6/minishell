/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewpark <jaewpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:03:50 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 16:59:13 by jaewpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	ft_env(void)
{
	t_env	*env;

	env = g_info.env;
	while (env)
	{
		if (!ft_strcmp(env->key, "?") || !env->value)
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	return (TRUE);
}
