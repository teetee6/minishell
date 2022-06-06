/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:03:55 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 22:03:56 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

int	lexer(char *line)
{
	int	size;
	int	ret_fn;

	size = (int)ft_strlen(line);
	ret_fn = 0;
	if (check_quote_opened(line, size) == QUOTE_ERROR)
		return (QUOTE_ERROR);
	ret_fn = tokenize(line);
	if (ret_fn != 0)
		return (ret_fn);
	ret_fn = replace_env();
	if (ret_fn != 0)
		return (ret_fn);
	ret_fn = strip_quotes();
	if (ret_fn != 0)
		return (ret_fn);
	return (0);
}

int	tokenize(char *line)
{
	int		state;
	int		i;
	t_tok	*token;

	g_info.lexerbuf = malloc(sizeof(t_lexer));
	token = create_tok();
	if (!g_info.lexerbuf || !token)
		return (-1);
	g_info.lexerbuf->ntoks = 0;
	g_info.lexerbuf->llisttok = token;
	state = STATE_GENERAL;
	i = -1;
	while (line[++i])
	{
		if (state == STATE_GENERAL)
			write_in_state_general(&token, line, &i, &state);
		else if (state == STATE_IN_DQUOTE || state == STATE_IN_QUOTE)
			write_in_state_quote_opened(token, &state, line[i]);
	}
	delete_trash(&g_info.lexerbuf->llisttok);
	if (not_interpret_exception(&g_info.lexerbuf->llisttok) == NO_INTERPRET)
		return (NO_INTERPRET);
	return (check_syntax());
}
