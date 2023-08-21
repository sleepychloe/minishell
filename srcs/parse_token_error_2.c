/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_error_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 03:38:41 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/29 03:40:19 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	token_redir_in_err(char *line, int i)
{
	if (line[i + 1] && line[i + 1] != '<'
		&& line[i + 1] != ' ' && !ft_isalnum(line[i + 1]))
	{
		if (line[i + 1] == '|')
			return (token_err_msg("|"), 1);
		return (token_err_msg("<"), 1);
	}
	if (line[i + 1] && line[i + 1] == '<'
		&& line[i + 2] && (line[i + 2] != ' ' && !ft_isalnum(line[i + 2])))
	{
		if (line[i + 2] == '|')
			return (token_err_msg("|"), 1);
		return (token_err_msg("<<"), 1);
	}
	return (0);
}

int	token_redir_out_err(char *line, int i)
{
	if (line[i + 1] && line[i + 1] != '>'
		&& line[i + 1] != ' ' && !ft_isalnum(line[i + 1]))
	{
		if (line[i + 1] == '|')
			return (token_err_msg("|"), 1);
		return (token_err_msg(">"), 1);
	}
	if (line[i + 1] && line[i + 1] == '>'
		&& line[i + 2] && line[i + 2] != ' ' && !ft_isalnum(line[i + 2]))
	{
		if (line[i + 2] == '|')
			return (token_err_msg("|"), 1);
		return (token_err_msg(">>"), 1);
	}
	return (0);
}

int	token_semicolon_err(void)
{
	return (token_err_msg(";"), 1);
}

int	token_backslash_err(void)
{
	return (token_err_msg("\\"), 1);
}
