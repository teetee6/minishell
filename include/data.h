/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:44:41 by hyoslee           #+#    #+#             */
/*   Updated: 2022/05/28 21:44:44 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <term.h>
# include "../lib/include/libft.h"

# define TRUE 1
# define FALSE 0

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

# define REDIR_IN	1
# define REDIR_OUT	2
# define REDIR_APP	3
# define F_PIPE		4

# define NOTF		2
# define IS_DIR		3
# define NSFD		4

# define CMD_ECHO 1
# define CMD_CD 2
# define CMD_PWD 3
# define CMD_EXPORT 4
# define CMD_UNSET 5
# define CMD_ENV 6
# define CMD_EXIT 7

# define KEY_ARROW_UP 4283163
# define KEY_ARROW_DOWN 4348699
# define KEY_BSPACE 127
# define KEY_EOF 4
# define RE_LOOP 55

# define NO_SPECIFIED_ENV_SYMBOL -5
# define ONLY_ENV_SYMBOL -6
# define NO_INTERPRET -2
# define SYNTAX_ERROR -3
# define M_ERROR -1

# define ERROR_NSFD 71
# define SIGINT_HEREDOC 72
# define CD_HOME_NOTSET 73
# define CD_NSFD 74
# define EXPORT_NOT_VALID 75
# define EXIT_TOO_MANY_ARGS 76

# define QUOTE_ERROR 56

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define BLUE "\x1b[34m"
# define YELLOW "\x1b[33m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

typedef enum e_token_type
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_TWO_GREATER = 15934,
	CHAR_TWO_LESSER = 15420,
	CHAR_NULL = 0,
	TOKEN = -1,
}	t_token_type;

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_CMDPATH,
	NODE_ARGUMENT,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_APPEND,
	NODE_REDIRECT_HEREDOC,
}	t_node_type;

typedef enum e_token_state
{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_GENERAL,
}	t_token_state;

typedef enum e_has_pipe
{
	HAS_NO_PIPE,
	HAS_IN_PIPE,
	HAS_OUT_PIPE,
	HAS_BOTH_PIPE
}	t_has_pipe;

typedef struct s_env
{
	struct s_env		*next;
	char				*key;
	char				*value;
}	t_env;

/*
** history save
*/

typedef struct s_history
{
	char				*save;
	char				*tmp;
	struct s_history	*prev;
	struct s_history	*next;
}	t_history;

typedef struct s_tok
{
	char			*data;
	int				datasize;
	int				type;
	struct s_tok	*next;
	struct s_tok	*prev;
}	t_tok;

typedef struct s_lexer
{
	t_tok		*llisttok;
	int			ntoks;
}	t_lexer;

typedef struct s_astnode
{
	int					type;
	char				*data;
	struct s_astnode	*left;
	struct s_astnode	*right;
}	t_astnode;

typedef struct s_pipeinfo
{
	int	has_in_pipe;
	int	has_out_pipe;
	int	cmd_pipe[2];
}	t_pipeinfo;

typedef struct s_cmdinfo
{
	int			argc;
	char		**argv;
	t_pipeinfo	pipeinfo;
	int			redir_pipe[2];
	int			redir_in;
	int			redir_out;
}	t_cmdinfo;

/*
** global state
** ret: exit status code
*/

typedef struct s_info
{
	int					ret;
	t_history			*hist_lst;
	t_history			*hist_ptr;
	t_env				*env;
	struct termios		term_orig;
	struct termios		term_mod;
	t_lexer				*lexerbuf;
	t_astnode			*astnode;
	t_list				*here_str_lst;
	t_list				*outfd_lst;
	int					is_in_here;
	int					is_in_cat_wc;
	int					stdin_fd;
	int					stdout_fd;
}	t_info;

#endif
