/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:04:00 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 22:04:00 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	env_parse(char *envp[])
{
	int		i;
	t_env	*new;

	i = -1;
	while (envp[++i])
	{
		new = env_new(envp[i]);
		if (!new)
			return (-1);
		env_add_back(&(g_info.env), new);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->key = ft_strdup("?");
	new->value = ft_itoa(-11111);
	new->next = NULL;
	env_add_back(&(g_info.env), new);
	return (1);
}
