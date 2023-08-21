/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:50:20 by yhwang            #+#    #+#             */
/*   Updated: 2023/06/01 06:15:33 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->command)
			free(cmd[i]->command);
		if (cmd[i]->option)
			free_2d_arr(cmd[i]->option);
		if (cmd[i]->redir)
		{
			if (cmd[i]->redir->file_name)
				free(cmd[i]->redir->file_name);
			free(cmd[i]->redir);
		}
		free(cmd[i]);
	}
	if (cmd)
		free(cmd);
}
