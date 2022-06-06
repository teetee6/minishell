/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:04:12 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 22:04:13 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

t_env	*env_new(char *str)
{
	t_env	*new;
	int		i;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new->next = 0;
	if (str[i] != '=')
	{
		new->key = ft_substr(str, 0, i);
		new->value = 0;
		return (new);
	}
	new->key = ft_substr(str, 0, i);
	new->value = ft_substr(str + i + 1, 0, ft_strlen(str + i + 1));
	return (new);
}

void	env_add_back(t_env **lst, t_env *new)
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

void	clear_env(void)
{
	t_env	*node;
	t_env	*del_node;

	node = g_info.env;
	while (node)
	{
		if (node->key)
		{
			free(node->key);
			node->key = NULL;
		}
		if (node->value)
		{
			free(node->value);
			node->value = NULL;
		}
		del_node = node;
		node = node->next;
		free(del_node);
	}
	g_info.env = NULL;
}

char	*env_search(char *search_key)
{
	t_env	*node;

	node = g_info.env;
	if (!ft_strcmp("?", search_key))
	{
		while (node)
		{
			if (!ft_strcmp("?", node->key))
			{
				free(node->value);
				node->value = ft_itoa(g_info.ret);
				return (ft_strdup(node->value));
			}
			node = node->next;
		}
	}
	while (node)
	{
		if (!ft_strcmp(node->key, search_key))
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (ft_strdup(""));
}

void	find_env_and_replace(char **line)
{
	int		i;
	int		j;
	char	*env;

	i = -1;
	while (++i < (int)ft_strlen(*line))
	{
		if ((*line)[i] == '$')
		{
			j = i + 1;
			while (j < (int)ft_strlen(*line)
				&& (*line)[j] != ' '
				&& (*line)[j] != '$' && (*line)[j] != ';'
				&& (*line)[j] != '\"' && (*line)[j] != '\'')
				j++;
			if (j == i + 1)
				continue ;
			env = ft_substr(*line, i + 1, j - i - 1);
			replace_env3(line, i, j - 1, env_search(env));
			free(env);
			i = j - 1;
		}
	}
}
