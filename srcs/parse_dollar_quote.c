/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 04:08:24 by yhwang            #+#    #+#             */
/*   Updated: 2023/06/01 04:08:57 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	remove_dollar(char *line)
{
	int	i;
	int	pos;

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
		if (line[i] == '$')
		{
			if (line[i + 1] != '\0'
				&& (line[i + 1] == '\'' || line[i + 1] == '"'))
			{
				line = remove_str_from_line(line, i, ft_strlen("$"));
				i--;
			}
		}
		i++;
	}
}

void	remove_quote(char *line)
{
	char	quote;
	int		i;
	int		pos;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			line = remove_str_from_line(line, i, ft_strlen("'"));
			pos = find_c_pos(line, quote, i);
			line = remove_str_from_line(line, pos, ft_strlen("'"));
			i = pos - 1;
		}
		i++;
	}
}
