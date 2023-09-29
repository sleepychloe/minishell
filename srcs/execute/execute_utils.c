/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:43:54 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/24 15:17:54 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**remove_element_from_env(char **env, char *to_remove)
{
	char	**new_env;
	int		flag;
	int		i;
	int		j;

	flag = 0;
	i = -1;
	while (env[++i])
	{
		if ((!ft_strncmp(env[i], to_remove, ft_strlen(to_remove))
				&& env[i][ft_strlen(to_remove)] == '='))
			flag++;
	}
	if (!flag)
		return (env);
	new_env = (char **)ft_calloc(sizeof(char *), i);
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (!(!ft_strncmp(env[i], to_remove, ft_strlen(to_remove))
				&& env[i][ft_strlen(to_remove)] == '='))
			new_env[j++] = ft_strdup(env[i]);
	}
	return (free_2d_arr(env), new_env);
}

int	is_builtin_cmd(char *command)
{
	if ((!ft_strncmp(command, "echo", 4) && ft_strlen(command) == 4)
		|| (!ft_strncmp(command, "env", 3) && ft_strlen(command) == 3)
		|| (!ft_strncmp(command, "unset", 5) && ft_strlen(command) == 5)
		|| (!ft_strncmp(command, "export", 6) && ft_strlen(command) == 6)
		|| (!ft_strncmp(command, "cd", 2) && ft_strlen(command) == 2)
		|| (!ft_strncmp(command, "pwd", 3) && ft_strlen(command) == 3)
		|| (!ft_strncmp(command, "exit", 4) && ft_strlen(command) == 4))
		return (1);
	return (0);
}

char	*append_str_to_alloced_str(char *str1, char *str2)
{
	char	*res;
	int		i;

	res = ft_calloc(sizeof(char *), (ft_strlen(str1) + ft_strlen(str2) + 1));
	i = 0;
	while (str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	i = 0;
	while (str2[i])
	{
		res[ft_strlen(str1) + i] = str2[i];
		i++;
	}
	free(str1);
	return (res);
}

char	*append_num_to_alloced_str(char *str1, int num)
{
	char	*res;
	char	*tmp;
	int		i;

	tmp = ft_itoa(num);
	res = ft_calloc(sizeof(char *), ft_strlen(str1) + ft_strlen(tmp) + 1);
	i = 0;
	while (str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	i = 0;
	while (tmp[i])
	{
		res[ft_strlen(str1) + i] = tmp[i];
		i++;
	}
	free(str1);
	free(tmp);
	return (res);
}
