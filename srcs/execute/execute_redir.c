/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:43:34 by yhwang            #+#    #+#             */
/*   Updated: 2023/10/07 04:29:25 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	redir_open_file(t_data *cmd, int *in_fd, int *out_fd, int i)
{
	if (cmd->redir[i]->redir_flag == IN || cmd->redir[i]->redir_flag == HEREDOC)
	{
		*in_fd = open(cmd->redir[i]->file_name, O_RDONLY);
		if (*in_fd == -1)
		{
			stderr_msg("minishell: No such file or directory\n");
			cmd->exit = 1;
			return (0);
		}
	}
	if (cmd->redir[i]->redir_flag == OUT)
		*out_fd = open(cmd->redir[i]->file_name,
				O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (cmd->redir[i]->redir_flag == APPEND)
		*out_fd = open(cmd->redir[i]->file_name,
				O_CREAT | O_WRONLY | O_APPEND, 0664);
	return (1);
}

void	set_fd(t_data *cmd, int *in_fd, int *out_fd, int i)
{
	if (cmd->redir[i]->redir_flag == IN
		|| cmd->redir[i]->redir_flag == HEREDOC)
	{
		dup2(*in_fd, STDIN);
		close(*in_fd);
		if (cmd->redir[i]->redir_flag == HEREDOC)
			unlink(cmd->redir[i]->file_name);
	}
	else if (cmd->redir[i]->redir_flag == OUT
		|| cmd->redir[i]->redir_flag == APPEND)
	{
		dup2(*out_fd, STDOUT);
		close(*out_fd);
	}
}

int	redir_set_fd(t_data *cmd)
{
	int	in_fd;
	int	out_fd;
	int	i;

	i = -1;
	while (cmd->redir[++i])
	{
		if (!redir_open_file(cmd, &in_fd, &out_fd, i))
			return (0);
		set_fd(cmd, &in_fd, &out_fd, i);
	}
	return (1);
}
