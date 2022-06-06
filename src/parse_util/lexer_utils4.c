/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:24:32 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:24:33 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	check_quote_opened(char *line, int size)
{
	char	lastquote;
	char	c;
	int		i;

	lastquote = 0;
	i = -1;
	while (++i < size)
	{
		c = line[i];
		if ((c == '\'' || c == '\"') && lastquote == 0)
			lastquote = c;
		else if (c == lastquote)
			lastquote = 0;
	}
	if (lastquote)
		return (QUOTE_ERROR);
	return (0);
}

int	check_syntax(void)
{
	t_tok	*token;
	int		ret_fn;

	ret_fn = check_simple_syntax();
	if (ret_fn)
		return (ret_fn);
	token = g_info.lexerbuf->llisttok;
	while (token && token->next)
	{
		if (token->type != TOKEN && token->next->type != TOKEN)
		{
			if ((token->type == CHAR_PIPE && check_arrow_type(&token->next)))
			{
			}
			else
				return (SYNTAX_ERROR);
		}
		token = token->next;
	}
	if (token && token->type != TOKEN)
		return (SYNTAX_ERROR);
	return (0);
}

int	check_simple_syntax(void)
{
	t_tok	*token;

	count_list();
	token = g_info.lexerbuf->llisttok;
	if (g_info.lexerbuf->ntoks == 0)
		return (RE_LOOP);
	if (g_info.lexerbuf->ntoks == 1)
	{
		if (token->type != TOKEN)
			return (SYNTAX_ERROR);
	}
	if (token && token->type == CHAR_PIPE)
		return (SYNTAX_ERROR);
	return (0);
}

int	check_arrow_type(t_tok **curtok)
{
	if ((*curtok)->type == CHAR_LESSER
		|| (*curtok)->type == CHAR_GREATER
		|| (*curtok)->type == CHAR_TWO_GREATER
		|| (*curtok)->type == CHAR_TWO_LESSER)
	{
		return (TRUE);
	}
	return (FALSE);
}

int	not_interpret_exception(t_tok **token)
{
	t_tok	*cur_node;

	cur_node = *token;
	while (cur_node)
	{
		if (!ft_strcmp(cur_node->data, ";") || !ft_strcmp(cur_node->data, "\\"))
		{
			return (NO_INTERPRET);
		}
		cur_node = cur_node->next;
	}
	return (0);
}
