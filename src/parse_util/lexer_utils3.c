/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:24:30 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:24:30 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	getchartype(char c)
{
	if (c == '\'')
		return (CHAR_QOUTE);
	else if (c == '\"')
		return (CHAR_DQUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == ' ')
		return (CHAR_WHITESPACE);
	else if (c == '\\')
		return (CHAR_ESCAPESEQUENCE);
	else if (c == '\t')
		return (CHAR_TAB);
	else if (c == '\n')
		return (CHAR_NEWLINE);
	else if (c == '>')
		return (CHAR_GREATER);
	else if (c == '<')
		return (CHAR_LESSER);
	else if (c == 0)
		return (CHAR_NULL);
	return (CHAR_GENERAL);
}

int	find_env_symbol(char *line)
{
	int		i;
	int		n;
	char	lastquote;

	i = -1;
	lastquote = 0;
	n = ft_strlen(line);
	while (++i < n)
	{
		if ((line[i] == '\'' || line[i] == '\"') && lastquote == 0)
			lastquote = line[i];
		else if ((lastquote == '\"' || lastquote == 0) && line[i] == '$')
			return (i);
		else if (line[i] == lastquote)
			lastquote = 0;
	}
	return (NO_SPECIFIED_ENV_SYMBOL);
}

int	find_next_env(char *line, int *start, int *end)
{
	int	i;

	i = find_env_symbol(line);
	*start = i;
	if (i < 0)
		return (i);
	while (line[i])
	{
		if (ft_strchr(" /$\0", line[i + 1]) || line[i + 1] == '\''
			|| line[i + 1] == '\"')
			break ;
		i++;
	}
	if (line[i] == '$')
		return (ONLY_ENV_SYMBOL);
	*end = i;
	return (0);
}
