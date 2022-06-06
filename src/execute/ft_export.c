/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewpark <jaewpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:03:50 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 17:07:37 by jaewpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	ft_export(t_cmdinfo *cmdinfo, int *err_code)
{
	int		i;
	int		ret_code;
	t_env	*env;

	i = 0;
	if (cmdinfo->argc == 1)
		print_export();
	else
	{
		while (cmdinfo->argv[++i])
		{
			ret_code = check_char_is_valid(cmdinfo->argv[i]);
			if (ret_code < 0)
				error_export(cmdinfo->argv[i], err_code);
			else if (ret_code > 0)
			{
				if (env_change2(cmdinfo->argv[i]) == 0)
				{
					env = env_new(cmdinfo->argv[i]);
					env_add(&(g_info.env), env);
				}
			}
		}
	}
	return (TRUE);
}

int	env_change2(char *line)
{
	t_env	*tmp;
	int		i;
	char	*value;
	char	*key;

	tmp = g_info.env;
	i = find_end_of_key(line);
	key = ft_substr(line, 0, i);
	value = ft_substr(line + i + 1, 0, ft_strlen(line + i + 1));
	if (!value)
		value = strdup("");
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (change_env_value(tmp, line[i], key, value));
		tmp = tmp->next;
	}
	free(value);
	free(key);
	return (0);
}

int	change_env_value(t_env *tmp, char delimiter, char *key, char *value)
{
	if (tmp->value && delimiter == '=')
		free(tmp->value);
	if (delimiter == '=')
		tmp->value = value;
	else
		free(value);
	free(key);
	return (1);
}
