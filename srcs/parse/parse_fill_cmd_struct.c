/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_cmd_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 02:26:04 by yhwang            #+#    #+#             */
/*   Updated: 2023/08/23 02:27:41 by yhwang           ###   ########.fr       */
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

void	fill_option(t_data **cmd, char **split_cmd, int cmd_i)
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
}


void	fill_redir(t_data **cmd, char **split_cmd, int cmd_i)
{
	int	i;

	if (cmd[cmd_i]->redir->redir_flag == NONE)
	{
		cmd[cmd_i]->redir->file_name = ft_strdup("");
		return ;
	}
	i = -1;
	while (split_cmd[++i])
	{
		if (is_redir(split_cmd[i]))
			break ;
	}
	i++;
	cmd[cmd_i]->redir->file_name = ft_strdup(split_cmd[i]);
}

void	check_redir(t_data **cmd, char *each_cmd, char **split_cmd, int cmd_i)
{
	int	i;

	i = 0;
	cmd[cmd_i]->redir->redir_flag = -1;
	while (each_cmd[i] && cmd[cmd_i]->redir->redir_flag == -1)
	{
		if (each_cmd[i] == '<')
		{
			if (each_cmd[i + 1] && each_cmd[i + 1] == '<')
				cmd[cmd_i]->redir->redir_flag = HEREDOC;
			else
				cmd[cmd_i]->redir->redir_flag = IN;
		}
		if (each_cmd[i] == '>')
		{
			if (each_cmd[i + 1] && each_cmd[i + 1] == '>')
				cmd[cmd_i]->redir->redir_flag = APPEND;
			else
				cmd[cmd_i]->redir->redir_flag = OUT;
		}
		i++;
	}
	if (cmd[cmd_i]->redir->redir_flag == -1)
		cmd[cmd_i]->redir->redir_flag = NONE;
	fill_redir(cmd, split_cmd, cmd_i);
}

t_data	**fill_cmd_struct(t_data **cmd, char *each_cmd, int cmd_i)
{
	char	**split_each_cmd;
	int		option;

	/* split the command(=splited by pipe) by space,
		so that we can save command and options */
	split_each_cmd = ft_split(each_cmd, ' ');
	/* for counting options */
	option = 0;
	/* if <, >, <<, >> is detected, increase option */
	while (split_each_cmd[option])
		option++;
	/* when option is 0: there is no command(only spaces) */
	if (!(option))
	{
		/* free the split_each_cmd and cmd struct, return NULL as cmd struct */
		free_2d_arr(split_each_cmd);
		return (free_cmd(cmd), NULL);
	}
	/* alloc optionand copy the command(first one) */
	cmd[cmd_i]->command = ft_strdup(split_each_cmd[0]);
	/* alloc option and redir */
	cmd[cmd_i]->option = ft_calloc(sizeof(char *), option);
	cmd[cmd_i]->redir = ft_calloc(sizeof(t_redir *), 2);
	/* error check: malloc */
	if (!cmd[cmd_i]->option || !cmd[cmd_i]->redir)
	{
		printf("%sError: malloc error%s\n", RED, BLACK);
		/* free the split_each_cmd and cmd struct, return NULL as cmd struct */
		free_2d_arr(split_each_cmd);
		return (free_cmd(cmd), NULL);
	}
	/* fill option: regard option as the things after command(second, third, ...) */
	fill_option(cmd, split_each_cmd, cmd_i);
	/* check redirection: <, >, <<, >> if there is, else put NONE,
		and save filename to the cmd->redir */
	check_redir(cmd, each_cmd, split_each_cmd, cmd_i);
	/* free split_each_cmd and return cmd struct */
	return (free_2d_arr(split_each_cmd), cmd);
}
