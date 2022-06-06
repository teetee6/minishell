/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:04:35 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 22:04:35 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_info	g_info;

void	free_now_cmd(void)
{
	if (g_info.astnode)
	{
		ast_node_delete(g_info.astnode);
		g_info.astnode = NULL;
	}
	if (g_info.lexerbuf)
		clear_lexer();
	if (g_info.here_str_lst)
		ft_lstclear(&g_info.here_str_lst, free);
	if (g_info.outfd_lst)
		ft_lstclear(&g_info.outfd_lst, free);
}

void	free_all(void)
{
	if (g_info.env)
		clear_env();
	if (g_info.hist_lst)
		clear_history();
	free_now_cmd();
}

void	print_message(int ret_fn)
{
	if (ret_fn == -1)
		ft_putstr_fd(RED "malloc error\n" RESET, 1);
	if (ret_fn == QUOTE_ERROR)
		ft_putstr_fd(RED "Quote must be closed in pair\n" RESET, 1);
	if (ret_fn == KEY_EOF)
		ft_putstr_fd(BLUE "BYE\n" RESET, 1);
	if (ret_fn == NO_INTERPRET)
		ft_putstr_fd(RED "\\ or ; not interpret\n" RESET, 1);
	if (ret_fn == SYNTAX_ERROR)
		ft_putstr_fd(RED "SYNTAX ERROR\n" RESET, 1);
}

void	set_retcode(int ret_fn)
{
	if (ret_fn == -1)
		g_info.ret = 1;
	if (ret_fn == QUOTE_ERROR)
		g_info.ret = 1;
	if (ret_fn == NO_INTERPRET)
		g_info.ret = 1;
	if (ret_fn == SYNTAX_ERROR)
		g_info.ret = 1;
}
