/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:52:45 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/24 05:04:27 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

long long	ft_atolonglong(char *str)
{
	int			i;
	int			sign;
	long long	nb;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (sign * nb);
}

int	is_num_str(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(t_data *cmd)
{
	int	exit_status;

	if (cmd->pid == PARENTS)
		ft_putstr_fd("exit\n", STDERR);
	if (!cmd->option[0])
		exit_status = 0;
	else
	{
		if (!is_num_str(cmd->option[0])
			|| ft_atolonglong(cmd->option[0]) < LONG_MIN
			|| ft_atolonglong(cmd->option[0]) > LONG_MAX)
		{
			stderr_msg("minishell: exit: numeric argument required\n");
			exit_status = 2;
		}
		else if (cmd->option[1])
		{
			stderr_msg("minishell: exit: too many arguments\n");
			cmd->exit = 1;
			return ;
		}
		else
			exit_status = (long)ft_atolonglong(cmd->option[0]);
	}
	cmd->exit = exit_status;
}
