/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:22:04 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:22:05 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	write_in_state_general(t_tok **token, char *line, int *i, int *state)
{
	char	c;
	int		chtype;

	c = line[*i];
	chtype = getchartype(c);
	if (ft_strchr("\'\"\\", chtype) || chtype == CHAR_GENERAL)
	{
		if (ft_concat_general_wrapper(*token, c, state) == -1)
			return (-1);
	}
	else if (chtype == ' ')
	{
		if ((*token)->data)
		{
			if (ft_append_new_token(token) == -1)
				return (-1);
		}
	}
	return (write_in_state_general2(token, line, i));
}

int	write_in_state_general2(t_tok **token, char *line, int *i)
{
	char	c;
	int		chtype;

	c = line[*i];
	chtype = getchartype(c);
	if (ft_strchr("><|", chtype))
	{
		if ((*token)->data)
		{
			if (ft_append_new_token(token) == -1)
				return (-1);
		}
		if (!ft_concat_to_token_data(*token, c))
			return (-1);
		(*token)->type = c;
		if (set_if_two_arrow_tok(token, line, i) == -1)
			return (-1);
		if (ft_append_new_token(token) == -1)
			return (-1);
	}
	return (0);
}

int	write_in_state_quote_opened(t_tok *token, int *state, char c)
{
	int		chtype;

	chtype = getchartype(c);
	if (!ft_concat_to_token_data(token, c))
		return (-1);
	if ((*state == STATE_IN_DQUOTE && chtype == '\"')
		|| (*state == STATE_IN_QUOTE && chtype == '\''))
		*state = STATE_GENERAL;
	return (0);
}
