/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:50 by yhwang            #+#    #+#             */
/*   Updated: 2023/08/23 02:23:53 by yhwang           ###   ########.fr       */
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

# define SPACE			10
# define PIPE			11
# define END			14

# define NONE			1
# define IN			2
# define OUT			3
# define HEREDOC		4
# define APPEND			5

# define KEY			0
# define VALUE			1
# define TEMP			2

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
# include "../libft/incs/libft.h"

typedef struct s_redir
{
	int			redir_flag;
	char		*file_name;
}	t_redir;

typedef struct s_data
{
	char		*command;
	char		**option;
	t_redir		*redir;
	int			exit;
}	t_data;

extern int	g_exit_code;

/* 🐥 main 🐥 */
/* main.c */
char		**alloc_env(char **env);
void		signal_handler(int signo);
void		signal_detect(void);
int			minishell_main(t_data **cmd, char **env);
int			main(int argc, char **argv, char **env);

/* 🐥 parse 🐥 */
/* parse.c */
t_data		**alloc_cmd(t_data **cmd, int i);
t_data		**parse(t_data **cmd, char **env, char *rdline);

/* parse_token_error_1.c */
int			token_quote_err(char *line);
int			token_pipe_err(char *line, int i);
int			token_ampersand_err(char *line, int i);
int			token_err(char *line);

/* parse_token_error_2.c */
int			token_redir_in_err(char *line, int i);
int			token_redir_out_err(char *line, int i);
int			token_semicolon_err(void);
int			token_backslash_err(void);

/* parse_pos_error.c */
void		convert_line(char *line);
void		pos_err_msg(int flag);
int			check_pos_err(char *line, int *flag, int i);
char		*copy_line(char *line);
int			pos_err(char *line);

/* parse_make_new_line.c */
void		remove_dollar(char *line);
void		remove_quote(char *line);
char		*make_new_line(char **env, char *rdline);

/* parse_handle_env_variable.c */
char		*change_key_to_value(char *line,
				char *key, int pos_key_start, char *value);
char		*env_check_value(char **env, char *line, int start, int end);
char		*env_var_convert_line(char **env, char *line, int i);
void		handle_env_var_norminette(int *quote);
char		*handle_env_var(char **env, char *line);

/* parse_fill_cmd_struct.c */
void		fill_option(t_data **cmd, char **split_cmd, int cmd_i);
int			is_redir(char *str);
void		fill_redir(t_data **cmd, char **split_cmd, int cmd_i);
void		check_redir(t_data **cmd,
				char *each_cmd, char **split_cmd, int cmd_i);
t_data		**fill_cmd_struct(t_data **cmd, char *each_cmd, int cmd_i);

/* parse_utils.c */
void		minishell_header(void);
void		token_err_msg(char *s);
int			find_c_pos(char *str, char c, int start);
char		*remove_str_from_line(char *line, int str_start_pos, int str_len);

/* parse_lib_utils.c */
void		*ft_realloc(void *old_ptr, size_t old_len, size_t new_len);
void		free_2d_arr(char **arr);
void		free_cmd(t_data **cmd);

/* 🐥 execute 🐥 */
/* execute_main.c */
void		exec_main(t_data **cmd, char **env);

#endif
