/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:50 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/29 05:09:09 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BLACK			"\x1b[0m"
# define RED			"\x1b[31m"
# define CYAN			"\x1b[36m"
# define YELLOW			"\x1b[33m"

# define STDIN			0
# define STDOUT			1
# define STDERR			2

# define SPACE			1
# define PIPE			2
# define END			3

# define NONE			4
# define IN			5
# define OUT			6
# define HEREDOC		7
# define APPEND			8

# define _PIPE			10
# define _IN			11
# define _OUT			12
# define _SPACE			13

# define KEY			0
# define VALUE			1
# define TEMP			2

# define CHILD			0
# define PARENTS		1

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <asm/ioctl.h>
# include "../libft/incs/libft.h"
# include "../libft/incs/ft_printf.h"

typedef struct s_redir
{
	int			redir_flag;
	char		*file_name;
}	t_redir;

typedef struct s_data
{
	char		*command;
	char		**option;
	t_redir		**redir;
	int			exit;
	int			pid;
}	t_data;

/* global variable */
extern int	g_exit_code;

/* 🐥 main 🐥 */
/* main.c */
int			alloc_env(char ***env);
void		signal_handler(int signo);
void		signal_detect(void);
int			minishell_main(t_data **cmd, char ***env);
int			main(int argc, char **argv, char **env);

/* 🐥 parse 🐥 */
/* parse.c */
t_data		**alloc_cmd(t_data **cmd, int i);
t_data		**parse(t_data **cmd, char **env, char *rdline);

/* parse_token_error_1.c */
int			token_quote_err(char *line);
void		convert_inside_quote(char *line, int i);
int			token_pipe_err(char *line, int i);
int			token_ampersand_err(char *line, int i);
int			token_err(char *line);

/* parse_token_error_2.c */
int			token_redir_in_err(char *line, int i);
int			token_redir_out_err(char *line, int i);
int			token_semicolon_err(void);
int			token_backslash_err(void);

/* parse_pos_error.c */
char		*copy_line(char *line);
void		convert_line(char *line);
int			pos_err(char *line);

/* parse_pos_error_check.c */
void		pos_err_msg(int flag);
void		set_pos_flag(char *line, int *flag, int *i);
int			check_pos_flag(char *line, int *flag, int *i);
int			check_pos_err(char *line, int *flag, int *i);

/* parse_make_new_line.c */
void		remove_dollar(char *line);
void		remove_quote(char *line);
char		*put_space(char *line, int i, int redir_len, char redir);
char		*redir_put_space(char *line);
char		*make_new_line(char **env, char *rdline);

/* parse_handle_env_variable.c */
void		handle_env_var_norminette(int *quote);
char		*handle_env_var(char **env, char *line);

/* parse_convert_env_variable.c */
void		fill_new_line(char *new_line, char *value,
				char *line_before_env, char *line_after_env);
char		*change_key_to_value(char **line,
				char *key, int *pos_key_start, char *value);
char		*env_check_value(char **env, char *line, int *start, int end);
char		*env_var_convert_line(char **env, char *line, int *i);

/* parse_fill_cmd_struct.c */
int			is_redir(char *str);
void		fill_command(t_data **cmd, char **split_cmd, int cmd_i);
void		fill_option(t_data **cmd,
				char *each_cmd, char **split_cmd, int cmd_i);
void		revert_cmd(t_data **cmd);
t_data		**fill_cmd_struct(t_data **cmd, char *each_cmd, int cmd_i);

/* parse_fill_cmd_check_redir.c */
int			find_redir(char **split_cmd, int i);
void		fill_realloc_redir(t_data **cmd,
				char **split_cmd, int cmd_i, int i);
void		realloc_redir(t_data **cmd, char **split_cmd, int cmd_i, int flag);
void		fill_redir(t_data **cmd, char **split_cmd, int cmd_i);
void		check_redir(t_data **cmd,
				char *each_cmd, char **split_cmd, int cmd_i);

/* parse_utils.c */
void		minishell_header(void);
void		stderr_msg(char *str);
void		token_err_msg(char *s);
int			find_c_pos(char *str, char c, int start);
char		*remove_str_from_line(char *line, int str_start_pos, int str_len);

/* parse_lib_utils.c */
void		*ft_realloc(void *old_ptr, size_t old_len, size_t new_len);
void		free_2d_arr(char **arr);
void		free_cmd(t_data **cmd);
void		minishell_exit(t_data **cmd, char **env, char *err_msg);

/* 🐥 execute 🐥 */
/* execute_main.c */
void		check_pid(t_data **cmd_struct, t_data *cmd, char ***env);
void		execute_cmd(t_data **cmd_struct, t_data *cmd, char ***env);
void		wait_pid(t_data **cmd);
void		run_command(t_data **cmd_struct, t_data *cmd, char ***env, int *fd);
void		exec_main(t_data **cmd, char ***env);

/* execute_heredoc.c */
void		signal_handler_heredoc(int signo);
void		write_heredoc(int fd_heredoc, char *delim, int *flag);
void		run_heredoc(t_data **cmd, int i, int j, int *flag);
int			check_heredoc(t_data **cmd);

/* execute_pipe_fd.c */
void		alloc_pipe(t_data **cmd, int (**_pipe)[2]);
void		close_pipe(t_data **cmd, int (**_pipe)[2]);
void		set_fd_close_pipe(t_data **cmd, int (**_pipe)[2], int i);
void		set_fd_stdio(int *fd);
void		close_fd_stdio(int *fd);

/* execute_redir.c */
int			redir_open_file(t_data *cmd, int *in_fd, int *out_fd, int i);
void		set_fd(t_data *cmd, int *in_fd, int *out_fd, int i);
int			redir_set_fd(t_data *cmd);

/* execute_builtin_echo.c */
void		builtin_echo(t_data *cmd);

/* execute_builtin_env.c */
void		builtin_env(char **env);

/* execute_builtin_unset.c */
int			compare_env_var_name(char *env, char *str);
void		builtin_unset(t_data *cmd, char **env);

/* execute_builtin_export.c */
void		run_export_no_option(char **env);
void		run_export(char ***env, char *key_value);
int			check_identifier(char *str);
void		builtin_export(t_data *cmd, char ***env);

/* execute_builtin_cd.c */
char		*get_env_value(char **env, char *key);
void		add_element_to_env(char ***env, char *element_to_add);
void		update_pwd_oldpwd(char ***env, char *absolute_path);
void		run_cd(t_data *cmd, char ***env, char *option);
void		builtin_cd(t_data *cmd, char ***env);

/* execute_builtin_pwd.c */
void		builtin_pwd(void);

/* execute_builtin_exit.c */
long long	ft_atolonglong(char *str);
int			is_num_str(char *str);
void		builtin_exit(t_data *cmd);

/* execute_non_builtin.c */
char		*gain_env_value(char *key, char **env);
char		*find_cmd_path(t_data *cmd, char **env);
void		execute_non_builtin(t_data *cmd, char *cmd_with_path, char **env);
void		non_builtin(t_data *cmd, char **env);

/* execute_utils.c */
char		**remove_element_from_env(char **env, char *to_remove);
int			is_builtin_cmd(char *command);
char		*append_str_to_alloced_str(char *str1, char *str2);
char		*append_num_to_alloced_str(char *str1, int i);

#endif
