/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:56:18 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/23 04:45:22 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	builtin_echo(t_data *cmd)
{
	int	flag_option_n;
	int	i;

	if (cmd->option[0] && !ft_strncmp(cmd->option[0], "-n", 2)
		&& ft_strlen(cmd->option[0]) == 2)
	{
		flag_option_n = 1;
		i = 1;
	}
	else
	{
		flag_option_n = 0;
		i = 0;
	}
	while (cmd->option[i])
	{
		if ((i > 0 && !flag_option_n) || (i > 1 && flag_option_n))
			printf(" ");
		printf("%s", cmd->option[i]);
		i++;
	}
	if (!flag_option_n)
		printf("\n");
	cmd->exit = 0;
}
