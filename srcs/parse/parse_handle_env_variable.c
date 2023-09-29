/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handle_env_variable.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 04:02:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/25 19:29:01 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	handle_env_var_norminette(int *quote)
{
	if (*quote == 2)
		*quote = 0;
}

char	*handle_env_var(char **env, char *line)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (line[++i] != '\0')
	{
		if (line[i] == '"')
			quote++;
		handle_env_var_norminette(&quote);
		if (line[i] == '\'' && !quote)
		{
			i = find_c_pos(line, line[i], i + 1);
			continue ;
		}
		if (line[i] == '$' && (quote == 0 || quote == 1))
		{
			if (!(line[i + 1]) || (line[i + 1] && (line[i + 1] == '\''
						|| line[i + 1] == '"' || line[i + 1] == ' ')))
				break ;
			line = env_var_convert_line(env, line, &i);
		}
	}
	return (line);
}
