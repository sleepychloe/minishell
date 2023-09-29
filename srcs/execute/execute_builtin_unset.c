/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:57:21 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/21 15:34:15 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	compare_env_var_name(char *env, char *str)
{
	int		i;
	char	*env_to_find;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	env_to_find = malloc((sizeof(char) * i) + 1);
	if (!env_to_find)
		return (0);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		env_to_find[i] = env[i];
		i++;
	}
	env_to_find[i] = 0x00;
	if (ft_strcmp(env_to_find, str) == 0)
	{
		free(env_to_find);
		return (1);
	}
	free(env_to_find);
	return (0);
}

void	builtin_unset(t_data *cmd, char **env)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	while (cmd->option && cmd->option[k])
	{
		i = 0;
		while (env[i])
		{
			if (compare_env_var_name(env[i], cmd->option[k]) == 1)
			{
				free(env[i]);
				j = i;
				while (env[j])
				{
					env[j] = env[j + 1];
					j++;
				}
			}
			else
				i++;
		}
		k++;
	}
}
