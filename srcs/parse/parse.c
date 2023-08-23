/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 02:35:34 by yhwang            #+#    #+#             */
/*   Updated: 2023/08/23 02:29:46 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_data	**alloc_cmd(t_data **cmd, int i)
{
	cmd = ft_realloc(cmd, sizeof(t_data *) * (i + 1),
			sizeof(t_data *) * (i + 2));
	if (!cmd)
		return (printf("%sError: malloc error%s\n", RED, BLACK), NULL);
	cmd[i] = (t_data *)ft_calloc(sizeof(t_data), 2);
	if (!cmd[i])
	{
		printf("%sError: malloc error%s\n", RED, BLACK);
		return (free_cmd(cmd), NULL);
	}
	return (cmd);
}

t_data	**parse(t_data **cmd, char **env, char *rdline)
{
	char	*line;
	char	**split_pipe;
	int		i;

	/* command line error check: quote, pipe, empersand, redirect, semicolon, backslash */
	if (token_quote_err(rdline) || token_err(rdline) || pos_err(rdline))
	{
		g_exit_code = 2;
		return (free_cmd(cmd), NULL);
	}
	/* make new command line: handle env variable, remove dollar sign */
	line = make_new_line(env, rdline);
	printf("%sline: %s%s\n", CYAN, line, BLACK);//erase later
	/* split the command by pipe */
	split_pipe = ft_split(line, '|');
	/* free the original command line */
	free(line);
	i = -1;
	/* put command info to the cmd structure */
	while (split_pipe[++i])
	{
		/* alloc cmd structure */
		cmd = alloc_cmd(cmd, i);
		/* error check: malloc */
		if (!cmd)
			return (free_2d_arr(split_pipe), NULL);
		/* fill the command info to the cmd struct */
		cmd = fill_cmd_struct(cmd, split_pipe[i], i);
		/* check if any error happened and free split_pipe if there was error
			: if any error has happened during filling the info,
			cmd was freed and NULL was returned */
		if (!cmd)
			return (free_2d_arr(split_pipe), NULL);
	}
	/* free split_pipe after filling cmd struct */
	free_2d_arr(split_pipe);
	return (cmd);
}
