/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 02:28:36 by yhwang            #+#    #+#             */
/*   Updated: 2023/08/23 02:28:45 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	exec_main(t_data **cmd, char **env)
{
	int	i;
	int	j;

	(void)env;
	i = -1;
	printf("%s", YELLOW);
	while (cmd[++i])
	{
		printf("cmd[%d] command: %s\n", i, cmd[i]->command);
		j = -1;
		while (cmd[i]->option[++j])
			printf("  option[%d]: %s\n", j, cmd[i]->option[j]);
		if (cmd[i]->redir->redir_flag == IN)
			printf("  redir: IN, filename: %s\n", cmd[i]->redir->file_name);
		else if (cmd[i]->redir->redir_flag == OUT)
			printf("  redir: OUT, filename: %s\n", cmd[i]->redir->file_name);
		else if (cmd[i]->redir->redir_flag == HEREDOC)
			printf("  redir: HEREDOC, filename: %s\n", cmd[i]->redir->file_name);
		else if (cmd[i]->redir->redir_flag == APPEND)
			printf("  redir: APPEND, filename: %s\n", cmd[i]->redir->file_name);
		else
			printf("  redir: NONE\n");
	}
	printf("%s", BLACK);
}
