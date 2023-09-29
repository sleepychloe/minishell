/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_cmd_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:51:02 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/29 03:26:57 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_redir(char *str)
{
	if ((!strncmp("<", str, 1) && ft_strlen(str) == 1)
		|| (!strncmp(">", str, 1) && ft_strlen(str) == 1)
		|| (!strncmp("<<", str, 1) && ft_strlen(str) == 2)
		|| (!strncmp(">>", str, 1) && ft_strlen(str) == 2))
		return (1);
	return (0);
}

void	fill_command(t_data **cmd, char **split_cmd, int cmd_i)
{
	if (!is_redir(split_cmd[0]))
		cmd[cmd_i]->command = ft_strdup(split_cmd[0]);
	else
		cmd[cmd_i]->command = ft_strdup("");
}

void	fill_option(t_data **cmd,
			char *each_cmd, char **split_cmd, int cmd_i)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd[cmd_i]->option[i] = NULL;
	while (split_cmd[++i])
	{
		if (is_redir(split_cmd[i]))
		{
			i++;
			continue ;
		}
		cmd[cmd_i]->option[j++] = ft_strdup(split_cmd[i]);
	}
	check_redir(cmd, each_cmd, split_cmd, cmd_i);
}

void	revert_cmd(t_data **cmd)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i]->option[++j])
		{
			k = -1;
			while (cmd[i]->option[j][++k])
			{
				if (cmd[i]->option[j][k] == _PIPE)
					cmd[i]->option[j][k] = '|';
				else if (cmd[i]->option[j][k] == _IN)
					cmd[i]->option[j][k] = '<';
				else if (cmd[i]->option[j][k] == _OUT)
					cmd[i]->option[j][k] = '>';
				else if (cmd[i]->option[j][k] == _SPACE)
					cmd[i]->option[j][k] = ' ';
			}
		}
	}
}

t_data	**fill_cmd_struct(t_data **cmd, char *each_cmd, int cmd_i)
{
	char	**split_each_cmd;
	int		option;

	split_each_cmd = ft_split(each_cmd, ' ');
	option = 0;
	while (split_each_cmd[option])
		option++;
	if (!(option))
	{
		free_2d_arr(split_each_cmd);
		return (free_cmd(cmd), NULL);
	}
	fill_command(cmd, split_each_cmd, cmd_i);
	cmd[cmd_i]->option = ft_calloc(sizeof(char *), option);
	cmd[cmd_i]->redir = ft_calloc(sizeof(t_redir **), 2);
	cmd[cmd_i]->redir[0] = ft_calloc(sizeof(t_redir *), 2);
	if (!cmd[cmd_i]->option || !cmd[cmd_i]->redir[0])
	{
		printf("%sError: malloc error%s\n", RED, BLACK);
		free_2d_arr(split_each_cmd);
		return (free_cmd(cmd), NULL);
	}
	fill_option(cmd, each_cmd, split_each_cmd, cmd_i);
	revert_cmd(cmd);
	return (free_2d_arr(split_each_cmd), cmd);
}
