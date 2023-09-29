/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pos_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:23:23 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/29 01:26:31 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*copy_line(char *line)
{
	char	*res;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(line);
	res = (char *)ft_calloc(sizeof(char), len + 2);
	if (!res)
		return (stderr_msg("Error: malloc error\n"), NULL);
	while (line[++i])
		res[i] = line[i];
	return (res);
}

void	convert_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			line[i] = SPACE;
		else if (line[i] == '|')
			line[i] = PIPE;
		else if (line[i] == '<')
			line[i] = IN;
		else if (line[i] == '>')
			line[i] = OUT;
		i++;
	}
	line[i] = END;
	line[i + 1] = '\0';
}

int	pos_err(char *line)
{
	int		i;
	int		pos;
	int		flag;
	char	*copy;

	i = 0;
	copy = copy_line(line);
	if (!copy)
		return (1);
	convert_line(copy);
	while (copy[i] != '\0')
	{
		if (copy[i] == '\'' || copy[i] == '"')
		{
			i++;
			pos = find_c_pos(line, line[i - 1], i);
			i = (pos + 1);
			continue ;
		}
		if (check_pos_err(copy, &flag, &i))
			return (free(copy), 1);
		i++;
	}
	free(copy);
	return (0);
}
