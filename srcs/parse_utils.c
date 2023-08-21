/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 04:10:48 by yhwang            #+#    #+#             */
/*   Updated: 2023/05/31 01:12:45 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	token_err_msg(char *s)
{
	printf("%sminishell: syntax error near unexpected token `%s'%s\n",
		RED, s, BLACK);
}

int	find_c_pos(char *str, char c, int start)
{
	int	i;

	i = start;
	if ((int)ft_strlen(str) <= start)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*remove_str_from_line(char *line, int str_start_pos, int str_len)
{
	int	i;

	i = str_start_pos + str_len - 1;
	while (line[++i] != '\0')
		line[i - str_len] = line[i];
	line[i - str_len] = '\0';
	return (line);
}
