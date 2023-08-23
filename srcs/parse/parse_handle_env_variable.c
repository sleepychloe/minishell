/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handle_env_variable.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 04:02:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/08/23 02:31:46 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*change_key_to_value(char *line,
			char *key, int pos_key_start, char *value)
{
	char	*line_before_env;
	char	*line_after_env;
	int		i;
	int		j;

	line_before_env = ft_substr(line, 0, pos_key_start);
	line_after_env = ft_substr(line, pos_key_start + ft_strlen(key),
			ft_strlen(line) - ft_strlen(line_before_env));
	line = ft_realloc(line, ft_strlen(line),
			ft_strlen(line_before_env) + ft_strlen(value)
			+ ft_strlen(line_after_env) + 1);
	i = -1;
	while (line_before_env[++i])
		line[i] = line_before_env[i];
	j = -1;
	while (value[++j])
		line[i++] = value[j];
	j = -1;
	while (line_after_env[++j])
		line[i++] = line_after_env[j];
	line[i] = '\0';
	free(key);
	free(value);
	free(line_before_env);
	return (free(line_after_env), line);
}

char	*env_check_value(char **env, char *line, int start, int end)
{
	char	*key_value[2];
	char	*temp;
	int		pos;
	int		i;

	while (line[end - 1] == '"' || line[end - 1] == '\'')
		end--;
	key_value[KEY] = ft_substr(line, start, end - start);
	key_value[VALUE] = NULL;
	i = -1;
	while (env[++i])
	{
		pos = find_c_pos(env[i], '=', 0);
		temp = ft_substr(env[i], 0, pos);
		if (!ft_strncmp(temp, key_value[KEY], ft_strlen(temp))
			&& ft_strlen(temp) == ft_strlen(key_value[KEY]))
			key_value[VALUE]
				= ft_substr(env[i], pos + 1, ft_strlen(env[i]) - (pos + 1));
		free(temp);
	}
	if (!key_value[VALUE] && key_value[KEY][0] == '?')
		key_value[VALUE] = ft_itoa(g_exit_code);
	else if (!key_value[VALUE])
		key_value[VALUE] = ft_strdup("");
	return (change_key_to_value(line, key_value[KEY], start, key_value[VALUE]));
}

char	*env_var_convert_line(char **env, char *line, int i)
{
	int	pos;

	remove_str_from_line(line, i, ft_strlen("$"));
	pos = find_c_pos(line, ' ', i);
	if (pos == -1)
		pos = ft_strlen(line);
	return (env_check_value(env, line, i, pos));
}

void	handle_env_var_norminette(int *quote)
{
	if (*quote == 2)
		*quote = 0;
}

char	*handle_env_var(char **env, char *line)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			quote++;
		handle_env_var_norminette(&quote);
		if (line[i] == '\'' && !quote)
		{
			i = find_c_pos(line, line[i], i + 1) + 1;
			continue ;
		}
		if (line[i] == '$' && (quote == 0 || quote == 1))
		{
			if (!(line[i + 1]) || (line[i + 1] && (line[i + 1] == '\''
						|| line[i + 1] == '"' || line[i + 1] == ' ')))
				break ;
			line = env_var_convert_line(env, line, i);
		}
		i++;
	}
	return (line);
}
