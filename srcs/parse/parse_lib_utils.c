/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lib_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:50:20 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/24 16:07:40 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	*ft_realloc(void *old_ptr, size_t old_len, size_t new_len)
{
	char	*new_ptr;

	new_ptr = malloc(new_len);
	if (!new_ptr)
		return (NULL);
	ft_bzero(new_ptr, new_len);
	ft_memcpy(new_ptr, old_ptr, old_len);
	free(old_ptr);
	return (new_ptr);
}

void	free_2d_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_cmd(t_data **cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->command)
			free(cmd[i]->command);
		if (cmd[i]->option)
			free_2d_arr(cmd[i]->option);
		j = -1;
		if (cmd[i]->redir)
		{
			while (cmd[i]->redir[++j])
			{
				if (cmd[i]->redir[j]->file_name)
					free(cmd[i]->redir[j]->file_name);
				free(cmd[i]->redir[j]);
			}
			free(cmd[i]->redir);
		}
		free(cmd[i]);
	}
	if (cmd)
		free(cmd);
}

void	minishell_exit(t_data **cmd, char **env, char *err_msg)
{
	if (cmd)
		free_cmd(cmd);
	if (env)
		free_2d_arr(env);
	if (err_msg)
		stderr_msg(err_msg);
}
