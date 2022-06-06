/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewpark <jaewpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:03:50 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 16:59:49 by jaewpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

static char	*envp_join(char *name, char *cont)
{
	char	*str;
	char	*tmp;

	str = ft_strjoin(name, "=");
	tmp = ft_strjoin(str, cont);
	free(str);
	return (tmp);
}

static int	env_cnt(void)
{
	int		i;
	t_env	*tmp;

	tmp = g_info.env;
	i = 0;
	while (tmp)
	{
		if (!ft_strcmp("?", tmp->key))
		{
			tmp = tmp->next;
			continue ;
		}
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**make_envp(void)
{
	char	**res;
	int		i;
	int		len;
	t_env	*env;

	i = 0;
	len = env_cnt();
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (0);
	env = g_info.env;
	while (i < len)
	{
		if (!ft_strcmp("?", env->key))
		{
			env = env->next;
			continue ;
		}
		res[i] = envp_join(env->key, env->value);
		env = env->next;
		i++;
	}
	res[i] = 0;
	return (res);
}

void	free_str(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free(str[i]);
	free(str);
}
