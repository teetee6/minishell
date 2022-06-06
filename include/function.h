/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewpark <jaewpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:50:22 by hyoslee           #+#    #+#             */
/*   Updated: 2022/06/03 11:30:47 by jaewpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "data.h"

/*
** system function
*/
# include <string.h>
# include <pwd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

/*
** astress*.c
*/
int			astree(void);
t_astnode	*job(t_tok **curtok, int *err_ch);
t_astnode	*job1(t_tok **curtok, int *err_ch);
t_astnode	*job2(t_tok **curtok, int *err_ch);
t_astnode	*cmd(t_tok **curtok, int *err_ch);
t_astnode	*simplecmd(t_tok **curtok, int *err_ch);
void		make_arrow_node(t_astnode **res, char *filename,
				t_token_type chartype, int *err_ch);
void		set_node_for_arrow_node(t_astnode *new, t_token_type chartype,
				char *filename, int *err_ch);
t_astnode	*cmd_append_simplecmd(t_tok **curtok, int *err_ch, t_astnode *res);
void		make_simplecmd_node(t_astnode **res, char *filename,
				int *err_ch);

/*
** pipe*.c
*/
void		execute(void);
int			execute_pipeline(t_astnode *jobnode1);
int			execute_command(t_astnode *cmdnode, t_pipeinfo pipeinfo);
int			execute_command_pipe_wrapper(t_astnode *cmdnode,
				t_pipeinfo pipeinfo);
void		close_all_pipe(t_pipeinfo *pipeinfo, int *pseudo_pipe);
void		has_multiple_pipelines(t_astnode **jobnode2, t_pipeinfo *pipeinfo,
				int *psuedo_pipe, int *ret_code);
void		execute_simple_command_wrapper(t_astnode *cmdnode,
				t_cmdinfo *cmdinfo, int *err_code);
void		execute_simple_command(t_cmdinfo *cmdinfo, int *err_code);
int			init_cmdinfo(t_astnode *simple_cmd_node, t_cmdinfo *cmdinfo);
int			init_cmdinfo2(t_astnode *arg_node, t_cmdinfo *cmdinfo);
void		set_cmdinfo(t_astnode *cmdnode, t_pipeinfo pipeinfo,
				t_cmdinfo *cmdinfo, int *err_code);
void		clear_cmdinfo(t_cmdinfo *cmdinfo);
void		destroy_cmdinfo(t_cmdinfo *cmdinfo);
void		execute_simple_command2(t_cmdinfo *cmdinfo,
				int *stdinfd, int *stdoutfd);

/*
** lexer*.c
*/
int			lexer(char *line);
int			tokenize(char *line);
int			write_in_state_general(t_tok **token, char *line,
				int *i, int *state);
int			write_in_state_general2(t_tok **token, char *line, int *i);
int			write_in_state_quote_opened(t_tok *token, int *state, char c);
t_tok		*create_tok(void);
int			ft_concat_general_wrapper(t_tok *token, int c, int *state);
char		*ft_concat_to_token_data(t_tok *token, int c);
int			ft_append_new_token(t_tok **token);
int			set_if_two_arrow_tok(t_tok **token, char *line, int *i);
int			replace_env(void);
int			replace_env2(t_tok *tok);
int			replace_env3(char **res, int start, int end, char *value);
int			strip_quotes(void);
int			strip_quotes2(t_tok *tok, int strlen);

/*
** parse*.c
*/
int			env_parse(char *envp[]);
int			handle_input(void);
int			handle_key(int c);
int			handle_key_eof(void);
int			save_key(int c);
int			del_last_char(void);
int			type_first_letter(int c);
int			type_not_less_than_two_letter(int c);
int			save_history(void);
void		check_input_empty(int *ret_fn);
void		check_input_all_whitespace(int *ret_fn);
void		clear_tmp_history(void);

/*
** *_utils.c
*/
void		ast_attach_binary_branch(t_astnode *root,
				t_astnode *leftNode, t_astnode *rightNode);
void		ast_node_set_type(t_astnode *node, t_node_type nodetype);
void		ast_node_set_data(t_astnode *node, char *data, int *err_ch);
void		ast_node_delete(t_astnode *node);
int			assert_type(int toketype, char **bufferptr,
				t_tok **curtok, int *err_ch);
t_env		*env_new(char *str);
void		env_add_back(t_env **lst, t_env *new);
void		clear_env(void);
char		*env_search(char *search_key);
void		find_env_and_replace(char **line);
void		handle_redir(t_astnode *cmdnode, t_cmdinfo *cmdinfo,
				int *has_redir_in_heredoc, int *err_code);
void		handle_redir_in(t_astnode *cmdnode,
				t_cmdinfo *cmdinfo, int *err_code);
void		handle_redir_heredoc_wrapper(t_astnode *cmdnode,
				t_cmdinfo *cmdinfo, int *err_code);
void		handle_redir_heredoc(t_astnode *cmdnode, t_cmdinfo *cmdinfo);
void		handle_redir_out_append(t_astnode *cmdnode);
void		wait_until_child_closed(int pid, int *status, int *save);
void		modify_stdin_stdout(t_cmdinfo *cmdinfo);
void		reset_stdin_stdout(void);
void		write_gnl(int file_fd, int write_fd);
int			get_next_line(int fd, char **line);
t_history	*ft_histnew(char *save);
void		ft_histadd_front(t_history **lst, t_history *new);
void		clear_history(void);
int			create_history(void);
int			history_up(void);
int			history_down(void);
void		cancel_current_history(void);
void		clear_lexer(void);
void		count_list(void);
void		delete_trash(t_tok **token);
void		delete_trash_front_loop(t_tok **token);
int			getchartype(char c);
int			find_env_symbol(char *line);
int			find_next_env(char *line, int *start, int *end);
int			check_quote_opened(char *line, int size);
int			check_syntax(void);
int			check_simple_syntax(void);
int			check_arrow_type(t_tok **curtok);
int			not_interpret_exception(t_tok **token);
int			ft_strcmp(const char *s1, const char *s2);
void		free_now_cmd(void);
void		free_all(void);
void		print_message(int ret_fn);
void		set_retcode(int ret_fn);
void		__init_write_open(t_pipeinfo *pipeinfo, int *psuedo_pipe);
void		__prev_write_close__cur_write_open(t_pipeinfo *pipeinfo,
				int *psuedo_pipe);
void		__cur_read_close__next_read_open(t_pipeinfo *pipeinfo,
				int *psuedo_pipe);
void		__prev_write_close(t_pipeinfo *pipeinfo, int *psuedo_pipe);
void		__final_read_close(t_pipeinfo *pipeinfo);
void		handler(int signo);

/*
** main.c
*/
void		init_info(void);
void		init_term(void);
int			loop2(void);
int			loop(void);
int			main(int argc, char *argv[], char *envp[]);

/*
**	Execute Relative 
*/
int			builtin(t_cmdinfo *cmdinfo, int *err_code);
int			ft_echo(t_cmdinfo *cmdinfo);
int			ft_pwd(void);
int			ft_env(void);
int			ft_unset(t_cmdinfo *cmdinfo, int *err_code);
int			ft_cd(t_cmdinfo *cmdinfo, int *err_code);
int			ft_export(t_cmdinfo *cmdinfo, int *err_code);
int			env_change2(char *line);
int			change_env_value(t_env *tmp, char delimiter,
				char *key, char *value);
int			check_char_is_valid(char *str);
int			find_end_of_key(char *str);
void		env_add(t_env **lst, t_env *new);
void		print_export(void);
void		error_export(char *str, int *err_code);

int			ft_exit(t_cmdinfo *cmdinfo, int *err_code);

void		print_cd_error(char *str, int *err_var);

void		parse_path(t_list **lst, t_cmdinfo *cmdinfo);
int			find_cmd_generally(t_cmdinfo *cmdinfo);
void		path_execute_wrapper(t_cmdinfo *cmdinfo, int *err_code);
void		path_execute(t_cmdinfo *cmdinfo, int *err_code);

int			find_cmd_directly(t_cmdinfo *cmdinfo, int *type);

char		**make_envp(void);
void		free_str(char **str);
void		execute_error(char *cmd, int type, int *err_code);
#endif
