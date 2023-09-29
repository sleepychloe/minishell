/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 02:35:34 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/24 15:28:29 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_data	**alloc_cmd(t_data **cmd, int i)
{
	cmd = ft_realloc(cmd, sizeof(t_data *) * (i + 1),
			sizeof(t_data *) * (i + 2));
	if (!cmd)
		return (stderr_msg("Error: malloc error\n"), NULL);
	cmd[i] = (t_data *)ft_calloc(sizeof(t_data), 2);
	if (!cmd[i])
	{
		stderr_msg("Error: malloc error\n");
		return (free_cmd(cmd), NULL);
	}
	return (cmd);
}

t_data	**parse(t_data **cmd, char **env, char *rdline)
{
	char	*line;
	char	**split_pipe;
	int		i;

	if (token_quote_err(rdline) || token_err(rdline) || pos_err(rdline))
	{
		g_exit_code = 2;
		return (free_cmd(cmd), NULL);
	}
	line = make_new_line(env, rdline);
	split_pipe = ft_split(line, '|');
	free(line);
	i = -1;
	while (split_pipe[++i])
	{
		cmd = alloc_cmd(cmd, i);
		if (!cmd)
			return (free_2d_arr(split_pipe), NULL);
		cmd = fill_cmd_struct(cmd, split_pipe[i], i);
		if (!cmd)
			return (free_2d_arr(split_pipe), NULL);
	}
	free_2d_arr(split_pipe);
	free(rdline);
	return (cmd);
}
