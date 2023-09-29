/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:42:19 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/24 16:33:13 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	signal_handler_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		ioctl(STDIN, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit_code = 130;
	}
}

void	write_heredoc(int fd_heredoc, char *delim, int *flag)
{
	char	*line;

	while (!(*flag))
	{
		signal(SIGINT, signal_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if (!line)
		{
			stderr_msg("minishell: warning: ");
			stderr_msg("here-document delimited by end-of-file\n");
			break ;
		}
		if (g_exit_code == 130)
			(*flag)++;
		if (!ft_strncmp(line, delim, ft_strlen(delim))
			&& ft_strlen(line) == ft_strlen(delim))
			break ;
		write(fd_heredoc, line, ft_strlen(line));
		write(fd_heredoc, "\n", 1);
		free(line);
	}
	if (line && !(*flag))
		free(line);
	close(fd_heredoc);
}

void	run_heredoc(t_data **cmd, int i, int j, int *flag)
{
	int		fd_heredoc;
	char	*file_name;

	if (cmd[i]->redir[j]->redir_flag == HEREDOC)
	{
		file_name = ft_strdup("/tmp/.heredoc_");
		file_name = append_num_to_alloced_str(file_name, (i * 10) + j);
		fd_heredoc = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		write_heredoc(fd_heredoc, cmd[i]->redir[j]->file_name, flag);
		free(cmd[i]->redir[j]->file_name);
		cmd[i]->redir[j]->file_name = file_name;
	}
}

int	check_heredoc(t_data **cmd)
{
	int		i;
	int		j;
	int		flag;

	i = -1;
	flag = 0;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i]->redir[++j])
			run_heredoc(cmd, i, j, &flag);
	}
	if (flag)
		return (1);
	return (0);
}
