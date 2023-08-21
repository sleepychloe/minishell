/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_error_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 04:11:57 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/31 01:42:41 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	token_quote_err(char *line)
{
	char	quote;
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	while (line[i] != '\0' && pos >= 0)
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			pos = find_c_pos(line, quote, i);
			i = (pos + 1);
			continue ;
		}
		i++;
	}
	if (pos == -1)
	{
		if (quote == '\'')
			return (token_err_msg("\'"), 1);
		return (token_err_msg("\""), 1);
	}
	return (0);
}

int	token_pipe_err(char *line, int i)
{
	if (line[i + 1] && (line[i + 1] != ' ' && !ft_isalnum(line[i + 1])))
	{
		if (line[i + 1] != '|')
			return (token_err_msg("|"), 1);
		return (token_err_msg("||"), 1);
	}
	return (0);
}

int	token_ampersand_err(char *line, int i)
{
	if (line[i + 1] && line[i + 1] == '&')
		return (token_err_msg("&&"), 1);
	return (token_err_msg("&"), 1);
}

int	token_err(char *line)
{
	int		i;
	int		pos;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			i++;
			pos = find_c_pos(line, line[i - 1], i);
			i = (pos + 1);
			continue ;
		}
		if ((line[i] == '|' && token_pipe_err(line, i))
			|| (line[i] == '&' && token_ampersand_err(line, i))
			|| (line[i] == '<' && token_redir_in_err(line, i))
			|| (line[i] == '>' && token_redir_out_err(line, i))
			|| (line[i] == ';' && token_semicolon_err())
			|| (line[i] == '\\' && token_backslash_err()))
			return (1);
		i++;
	}
	return (0);
}
