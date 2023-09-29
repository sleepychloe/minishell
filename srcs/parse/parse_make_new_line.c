/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_make_new_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 04:08:24 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/23 05:43:22 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

char	*put_space(char *line, int i, int redir_len, char redir)
{
	char	*str[5];

	str[0] = ft_substr(line, 0, i);
	str[1] = ft_substr(line, i + redir_len, ft_strlen(line) - 1);
	if (redir == '>')
	{
		if (redir_len == 1)
			str[2] = " > ";
		else
			str[2] = " >> ";
	}
	else
	{
		if (redir_len == 1)
			str[2] = " < ";
		else
			str[2] = " << ";
	}
	str[3] = ft_strjoin(str[0], str[2]);
	str[4] = ft_strjoin(str[3], str[1]);
	free(line);
	free(str[0]);
	free(str[1]);
	free(str[3]);
	return (str[4]);
}

char	*redir_put_space(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' || line[i] == '>')
		{
			if ((line[i + 1] && (line[i + 1] == '<' || line[i + 1] == '>')))
			{
				line = put_space(line, i, 2, line[i]);
				i = i + 3;
			}
			else
			{
				line = put_space(line, i, 1, line[i]);
				i = i + 2;
			}
		}
		i++;
	}
	return (line);
}

char	*make_new_line(char **env, char *rdline)
{
	char	*line;

	line = ft_strdup(rdline);
	remove_dollar(line);
	line = handle_env_var(env, line);
	remove_quote(line);
	line = redir_put_space(line);
	return (line);
}
