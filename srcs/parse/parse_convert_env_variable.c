/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_convert_env_variable.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:05:23 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/24 16:08:50 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	fill_new_line(char *new_line, char *value,
			char *line_before_env, char *line_after_env)
{
	int	i;
	int	j;

	i = -1;
	while (line_before_env[++i])
		new_line[i] = line_before_env[i];
	j = -1;
	if (value)
	{
		while (value[++j])
			new_line[i++] = value[j];
	}
	j = -1;
	while (line_after_env[++j])
		new_line[i++] = line_after_env[j];
}

char	*change_key_to_value(char **line,
			char *key, int *pos_key_start, char *value)
{
	char	*new_line;
	char	*line_before_env;
	char	*line_after_env;

	line_before_env = ft_substr((*line), 0, *pos_key_start);
	line_after_env = ft_substr((*line), *pos_key_start + ft_strlen(key),
			ft_strlen((*line)) - ft_strlen(line_before_env));
	new_line = ft_calloc(sizeof(char), (ft_strlen(line_before_env)
				+ ft_strlen(value) + ft_strlen(line_after_env) + 1));
	fill_new_line(new_line, value, line_before_env, line_after_env);
	*pos_key_start = *pos_key_start + ft_strlen(value) - 1;
	free(key);
	if (value)
		free(value);
	free(line_before_env);
	free(*line);
	*line = new_line;
	return (free(line_after_env), *line);
}

char	*env_check_value(char **env, char *line, int *start, int end)
{
	char	*key_value[2];
	int		i;

	key_value[KEY] = ft_substr(line, *start, end - *start + 1);
	key_value[VALUE] = NULL;
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], key_value[KEY], ft_strlen(key_value[KEY]))
			&& env[i][ft_strlen(key_value[KEY])] == '=')
		{
			key_value[VALUE] = ft_strdup(env[i]);
			key_value[VALUE] = remove_str_from_line(key_value[VALUE],
					0, ft_strlen(key_value[KEY]) + 1);
		}
	}
	return (change_key_to_value(&line,
			key_value[KEY], start, key_value[VALUE]));
}

char	*env_var_convert_line(char **env, char *line, int *i)
{
	int	pos;

	remove_str_from_line(line, *i, ft_strlen("$"));
	if (line[*i] == '?')
		return (change_key_to_value(&line,
				ft_strdup("?"), i, ft_itoa(g_exit_code)));
	pos = *i + 1;
	while ((line[pos] != '"' && line[pos] != '\'' && line[pos] != '$'
			&& line[pos] != ' ' && line[pos] != '\0'))
		pos++;
	pos--;
	return (env_check_value(env, line, i, pos));
}
