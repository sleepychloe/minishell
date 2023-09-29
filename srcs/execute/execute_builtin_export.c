/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:57:15 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/24 01:42:43 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	run_export_no_option(char **env)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (env[i])
	{
		key = ft_substr(env[i], 0, find_c_pos(env[i], '=', 0) + 1);
		value = ft_strdup(env[i]);
		value = remove_str_from_line(value, 0, find_c_pos(env[i], '=', 0) + 1);
		printf("declare -x %s\"%s\"\n", key, value);
		free(key);
		free(value);
		i++;
	}
}

void	run_export(char ***env, char *key_value)
{
	char	*key;
	int		pos;
	int		i;

	key_value = ft_strdup(key_value);
	if (!key_value)
		return ;
	pos = find_c_pos(key_value, '=', 0);
	if (pos == -1)
		return ;
	key = ft_substr(key_value, 0, pos);
	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp((*env)[i], key, ft_strlen(key))
			&& (*env)[i][ft_strlen(key)] == '=')
		{
			free((*env)[i]);
			(*env)[i] = key_value;
			free(key);
			return ;
		}
	}
	free(key);
	add_element_to_env(env, key_value);
}

int	check_identifier(char *str)
{
	int	i;

	i = -1;
	if (find_c_pos(str, '=', 0) == -1)
	{
		while (str[++i])
		{
			if (!(('a' <= str[i] && str[i] <= 'z')
					|| ('A' <= str[i] && str[i] <= 'Z')
					|| str[i] == '_'))
				return (0);
		}
	}
	else
	{
		while (str[++i] == '=')
		{
			if (!(('a' <= str[i] && str[i] <= 'z')
					|| ('A' <= str[i] && str[i] <= 'Z')
					|| str[i] == '_'))
				return (0);
		}
	}
	return (1);
}

void	builtin_export(t_data *cmd, char ***env)
{
	int	i;

	if (!cmd->option[0])
		run_export_no_option(*env);
	else
	{
		i = 0;
		while (cmd->option[i])
		{
			if (!check_identifier(cmd->option[i]))
			{
				stderr_msg("minishell: export: not a valid identifier\n");
				cmd->exit = 1;
				break ;
			}
			if (find_c_pos(cmd->option[i], '=', 0) != -1)
				run_export(env, cmd->option[i]);
			i++;
		}
	}
}
