# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 20:15:35 by hyoslee           #+#    #+#              #
#    Updated: 2022/03/18 20:15:39 by hyoslee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Werror -Wextra
TFLAGS		= -lreadline -ltermcap
LIB_FLAGS	= -L./lib/ -l_hyoslee
AR			= ar rcs
RM			= rm -f

DIR_PARSE_UTIL = parse_util
DIR_PARSE = parse
DIR_EXECUTE = execute

SRC		=	$(DIR_PARSE_UTIL)/env_utils.c \
			$(DIR_PARSE_UTIL)/hist_utils.c $(DIR_PARSE_UTIL)/hist_utils2.c \
			$(DIR_PARSE_UTIL)/astree_utils.c \
			$(DIR_PARSE_UTIL)/lexer_utils.c $(DIR_PARSE_UTIL)/lexer_utils2.c \
			$(DIR_PARSE_UTIL)/lexer_utils3.c $(DIR_PARSE_UTIL)/lexer_utils4.c \
			$(DIR_PARSE_UTIL)/get_next_line.c $(DIR_PARSE_UTIL)/get_next_line_util.c \
			$(DIR_PARSE_UTIL)/pipe_utils.c $(DIR_PARSE_UTIL)/pipe_utils2.c \
			$(DIR_PARSE_UTIL)/pipe_utils3.c \
			$(DIR_PARSE_UTIL)/sig_utils.c $(DIR_PARSE_UTIL)/main_utils.c \
			$(DIR_PARSE_UTIL)/lib_utils.c \
			$(DIR_PARSE)/parse_env.c \
			$(DIR_PARSE)/parse_input.c $(DIR_PARSE)/parse_input2.c \
			$(DIR_PARSE)/save_history.c \
			$(DIR_PARSE)/lexer.c $(DIR_PARSE)/lexer2.c \
			$(DIR_PARSE)/lexer3.c $(DIR_PARSE)/lexer4.c \
			$(DIR_PARSE)/astree.c $(DIR_PARSE)/astree2.c $(DIR_PARSE)/astree3.c \
			$(DIR_PARSE)/pipe.c $(DIR_PARSE)/pipe2.c $(DIR_PARSE)/pipe3.c \
			$(DIR_EXECUTE)/execute.c \
			$(DIR_EXECUTE)/ft_echo.c $(DIR_EXECUTE)/ft_pwd.c \
			$(DIR_EXECUTE)/ft_env.c $(DIR_EXECUTE)/ft_unset.c \
			$(DIR_EXECUTE)/ft_cd.c $(DIR_EXECUTE)/ft_export.c \
			$(DIR_EXECUTE)/ft_export2.c $(DIR_EXECUTE)/ft_export3.c \
			$(DIR_EXECUTE)/ft_exit.c $(DIR_EXECUTE)/cmd_generally.c \
			$(DIR_EXECUTE)/cmd_directly.c \
			$(DIR_EXECUTE)/ft_env_utils.c \
			main.c

SRCS		=	$(addprefix ./src/, $(SRC))
OBJS		=	$(SRCS:.c=.o)

ESC_RESET           = \033[0m
ESC_FNT_BOLD        = \033[1m
ESC_FNT_FINE        = \033[2m
ESC_FNT_ITALIC      = \033[3m
ESC_FNT_ULINE       = \033[4m
ESC_CLR_BLACK       = \033[38;5;00m
ESC_CLR_RED         = \033[38;5;01m
ESC_CLR_GREEN       = \033[38;5;02m
ESC_CLR_YELLOW      = \033[38;5;03m
ESC_CLR_BLUE        = \033[38;5;04m
ESC_CLR_MAGENTA     = \033[38;5;05m
ESC_CLR_CYAN        = \033[38;5;06m
ESC_CLR_WHITE       = \033[38;5;07m
ESC_CLR_PINK        = \033[38;5;213m

.c.o :
	@$(CC) $(CFLAGS) -I./include/ -o $@ -c $?

$(NAME) : $(OBJS)
	@make -C ./lib/
	@$(CC) -o $(NAME) $(OBJS) -I./include/ $(LIB_FLAGS) $(TFLAGS)
	@echo "$(ESC_FNT_BOLD)$(ESC_CLR_YELLOW)[ lib successfully compiled !! ]$(ESC_RESET)"
	@echo "$(ESC_FNT_BOLD)$(ESC_CLR_YELLOW)[ $(NAME) successfully compiled !! ]$(ESC_RESET)"

all : $(NAME)

clean :
	@make -C ./lib/ clean
	@$(RM) $(OBJS)

fclean : clean
	@make -C ./lib/ fclean
	@$(RM) $(NAME)

re : clean all

PHONY	: all clean fclean re
