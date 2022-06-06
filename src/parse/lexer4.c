/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:22:08 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:22:09 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	replace_env(void)
{
	t_tok	*token;
	int		ret_fn;

	token = g_info.lexerbuf->llisttok;
	ret_fn = 0;
	while (token)
	{
		ret_fn = replace_env2(token);
		if (ret_fn == -1)
			return (ret_fn);
		token->datasize = ft_strlen(token->data);
		token = token->next;
	}
	delete_trash(&g_info.lexerbuf->llisttok);
	ret_fn = check_syntax();
	return (ret_fn);
}

int	replace_env2(t_tok *tok)
{
	int		start;
	int		end;
	char	*key;
	char	*value;
	int		ret_fn;

	!(start = 0) && (end = 0);
	value = NULL;
	while (1)
	{
		ret_fn = find_next_env(tok->data, &start, &end);
		if (ret_fn == ONLY_ENV_SYMBOL || ret_fn == NO_SPECIFIED_ENV_SYMBOL)
			return (ret_fn);
		key = ft_substr(tok->data, start + 1, end - start);
		if (!key)
			return (-1);
		value = env_search(key);
		if (!value)
			return (-1);
		free(key);
		ret_fn = replace_env3(&tok->data, start, end, value);
		if (ret_fn == -1)
			return (-1);
	}
	return (0);
}

int	replace_env3(char **res, int start, int end, char *value)
{
	int		ret_fn;
	char	*pre;
	char	*next;
	char	*str;

	ret_fn = 0;
	pre = ft_substr(*res, 0, start);
	next = ft_substr(*res, end + 1, ft_strlen(*res) - end);
	free(*res);
	str = ft_strjoin(pre, value);
	*res = ft_strjoin(str, next);
	if (!pre || !next || !str || !*res)
		ret_fn = -1;
	free(str);
	free(pre);
	free(next);
	free(value);
	return (ret_fn);
}

int	strip_quotes(void)
{
	t_tok	*token;
	int		ret_fn;

	ret_fn = 0;
	token = g_info.lexerbuf->llisttok;
	while (token)
	{
		if (strip_quotes2(token, ft_strlen(token->data)) == -1)
			return (-1);
		token->datasize = ft_strlen(token->data);
		token = token->next;
	}
	delete_trash(&g_info.lexerbuf->llisttok);
	ret_fn = check_syntax();
	return (ret_fn);
}

int	strip_quotes2(t_tok *tok, int strlen)
{
	char	*stripped;
	int		i;
	int		j;
	char	lastquote;

	if (strlen <= 1)
		return (0);
	stripped = malloc(tok->datasize + 1);
	if (!stripped)
		return (-1);
	!(lastquote = 0) && (j = -1);
	i = -1;
	while (++i < strlen)
	{
		if ((tok->data[i] == '\'' || tok->data[i] == '\"') && lastquote == 0)
			lastquote = tok->data[i];
		else if (tok->data[i] == lastquote)
			lastquote = 0;
		else
			stripped[++j] = tok->data[i];
	}
	stripped[++j] = 0;
	free(tok->data);
	tok->data = stripped;
	return (0);
}
