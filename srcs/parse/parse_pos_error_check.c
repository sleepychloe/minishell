/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pos_error_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 01:22:17 by yhwang            #+#    #+#             */
/*   Updated: 2023/10/07 04:30:09 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	pos_err_msg(int flag)
{
	if (flag == PIPE)
		token_err_msg("|");
	else if (flag == IN)
		token_err_msg("<");
	else if (flag == OUT)
		token_err_msg(">");
	else if (flag == HEREDOC)
		token_err_msg("<<");
	else if (flag == APPEND)
		token_err_msg(">>");
}

void	set_pos_flag(char *line, int *flag, int *i)
{
	if (line[*i] == IN && line[*i + 1] && line[*i + 1] == IN)
	{
		*flag = HEREDOC;
		*i = *i + 2;
	}
	else if (line[*i] == OUT && line[*i + 1] && line[*i + 1] == OUT)
	{
		*flag = APPEND;
		*i = *i + 2;
	}
	else
	{
		*flag = line[*i];
		(*i)++;
	}
}

int	check_pos_flag(char *line, int *flag, int *i)
{
	int	j;
	int	k;

	if (*flag == PIPE || *flag == IN || *flag == OUT || *flag == APPEND)
	{
		j = -1;
		k = 0;
		while (j <= *i && line[++j])
		{
			if (line[j] != END && line[j] != PIPE
				&& line[j] != IN && line[j] != OUT && line[j] != SPACE)
				k++;
		}
		if (k == 1)
			return (pos_err_msg(*flag), 1);
	}
	return (0);
}

int	check_pos_err(char *line, int *flag, int *i)
{
	while (line[*i] != END)
	{
		*flag = 0;
		if (line[*i] == PIPE || line[*i] == IN || line[*i] == OUT)
		{
			set_pos_flag(line, flag, i);
			if (check_pos_flag(line, flag, i))
				return (1);
			while (line[*i] == SPACE)
				(*i)++;
			if (line[*i] == END || line[*i] == PIPE
				|| line[*i] == IN || line[*i] == OUT)
				return (pos_err_msg(*flag), 1);
		}
		(*i)++;
	}
	return (0);
}
