/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:22:06 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/02 19:22:07 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

t_tok	*create_tok(void)
{
	t_tok	*tok;

	tok = malloc(sizeof(t_tok));
	if (!tok)
		return (NULL);
	tok->data = NULL;
	tok->datasize = 0;
	tok->type = CHAR_NULL;
	tok->next = NULL;
	tok->prev = NULL;
	return (tok);
}

int	ft_concat_general_wrapper(t_tok *token, int c, int *state)
{
	if (c == '\'')
		*state = STATE_IN_QUOTE;
	else if (c == '\"')
		*state = STATE_IN_DQUOTE;
	if (!ft_concat_to_token_data(token, c))
		return (-1);
	token->type = TOKEN;
	return (0);
}

char	*ft_concat_to_token_data(t_tok *token, int c)
{
	char	*new_str;
	char	*tmp;
	int		i;

	i = token->datasize;
	tmp = token->data;
	new_str = malloc(token->datasize + 2);
	if (!new_str)
		return (NULL);
	while (i-- > 0)
		new_str[i] = token->data[i];
	new_str[token->datasize] = c;
	new_str[token->datasize + 1] = '\0';
	token->datasize++;
	token->data = new_str;
	if (tmp)
		free(tmp);
	return (token->data);
}

int	ft_append_new_token(t_tok **token)
{
	t_tok	*new_token;

	new_token = create_tok();
	if (!new_token)
		return (-1);
	new_token->prev = *token;
	(*token)->next = new_token;
	*token = (*token)->next;
	return (0);
}

int	set_if_two_arrow_tok(t_tok **token, char *line, int *i)
{
	char	c;

	c = line[*i];
	if (line[*i + 1] == c && line[*i + 1] != '|')
	{
		if (!ft_concat_to_token_data(*token, c))
			return (-1);
		if (!ft_strcmp((*token)->data, "<<"))
			(*token)->type = CHAR_TWO_LESSER;
		else if (!ft_strcmp((*token)->data, ">>"))
			(*token)->type = CHAR_TWO_GREATER;
		*i = *i + 1;
	}
	return (0);
}
