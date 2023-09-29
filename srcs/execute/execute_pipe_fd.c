/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:43:17 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/18 05:26:44 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	alloc_pipe(t_data **cmd, int (**_pipe)[2])
{
	int	i;

	i = 0;
	*_pipe = NULL;
	while (cmd[i + 1])
	{
		*_pipe = ft_realloc(*_pipe, sizeof(int *) * i,
				sizeof(int *) * (i + 1));
		pipe((*_pipe)[i]);
		i++;
	}
}

void	close_pipe(t_data **cmd, int (**_pipe)[2])
{
	int	i;

	i = 0;
	while (cmd[i + 1])
	{
		close((*_pipe)[i][STDIN]);
		close((*_pipe)[i][STDOUT]);
		i++;
	}
}

void	set_fd_close_pipe(t_data **cmd, int (**_pipe)[2], int i)
{
	if (i > 0)
		dup2((*_pipe)[i - 1][STDIN], STDIN);
	if (cmd[i + 1])
		dup2((*_pipe)[i][STDOUT], STDOUT);
	close_pipe(cmd, _pipe);
	free(*_pipe);
}

void	set_fd_stdio(int *fd)
{
	fd[STDIN] = dup(STDIN);
	fd[STDOUT] = dup(STDOUT);
}

void	close_fd_stdio(int *fd)
{
	dup2(fd[STDIN], STDIN);
	dup2(fd[STDOUT], STDOUT);
	close(fd[STDIN]);
	close(fd[STDOUT]);
}
