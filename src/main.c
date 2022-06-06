/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:28:44 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 22:03:38 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_info	g_info;

void	init_info(void)
{
	g_info.ret = 0;
	g_info.hist_lst = NULL;
	g_info.hist_ptr = NULL;
	g_info.env = NULL;
	g_info.lexerbuf = NULL;
	g_info.astnode = NULL;
	g_info.here_str_lst = NULL;
	g_info.outfd_lst = NULL;
	g_info.is_in_here = FALSE;
	g_info.is_in_cat_wc = FALSE;
	g_info.stdin_fd = STDIN_FILENO;
	g_info.stdout_fd = STDOUT_FILENO;
}

void	init_term(void)
{
	char	*env;

	env = getenv("TERM");
	if (!env)
		env = "xterm";
	tcgetattr(STDIN_FILENO, &g_info.term_orig);
	tcgetattr(STDIN_FILENO, &g_info.term_mod);
	g_info.term_mod.c_lflag &= ~ICANON;
	g_info.term_mod.c_lflag &= ~ECHO;
	g_info.term_mod.c_cc[VMIN] = 1;
	g_info.term_mod.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_info.term_mod);
	tgetent(NULL, env);
}

int	loop2(void)
{
	int		ret_fn;

	ret_fn = handle_input();
	if (ret_fn != 0)
	{
		if (ret_fn == KEY_EOF)
			return (ret_fn);
		if (ret_fn == RE_LOOP)
			return (ret_fn);
		return (-1);
	}
	ret_fn = lexer(g_info.hist_lst->save);
	if (ret_fn != 0)
	{
		g_info.ret = 127;
		if (ret_fn == RE_LOOP)
			ft_putstr_fd(RED "EMPTY LINE\n" RESET, 1);
		return (ret_fn);
	}
	ret_fn = astree();
	if (ret_fn != 0)
		return (ret_fn);
	return (0);
}

int	loop(void)
{
	int		ret_fn;

	ret_fn = -1;
	while (1)
	{
		write(STD_OUT, "minishell$ ", 12);
		init_term();
		ret_fn = loop2();
		if (ret_fn != 0)
		{
			if (ret_fn == RE_LOOP)
			{
				free_now_cmd();
				continue ;
			}
			return (ret_fn);
		}
		if (g_info.astnode)
			execute();
		else
			g_info.ret = 1;
		free_now_cmd();
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	ret_fn;

	(void) argc;
	(void) argv;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	init_info();
	if (env_parse(envp) == -1)
		return (1);
	ret_fn = loop();
	free_all();
	print_message(ret_fn);
	set_retcode(ret_fn);
	return (g_info.ret);
}
