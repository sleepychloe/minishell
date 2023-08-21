/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:26:34 by yhwang            #+#    #+#             */
/*   Updated: 2023/08/21 19:31:22 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_exit_code;

void	signal_handler(int signo)
{
	/* ctrl - c */
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 130;
	}
	/* ctrl - \ */
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 127;
	}
}

void	signal_detect(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
