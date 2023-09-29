/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 01:28:57 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/24 16:29:32 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	check_pid(t_data **cmd_struct, t_data *cmd, char ***env)
{
	int	exit_code;

	if (cmd->pid == CHILD)
	{
		exit_code = cmd->exit;
		free_cmd(cmd_struct);
		free_2d_arr(*env);
		exit(exit_code);
	}
	if (cmd->pid == PARENTS && (!ft_strncmp(cmd->command, "exit", 4)
			&& ft_strlen(cmd->command) == 4))
	{
		exit_code = cmd->exit;
		free_cmd(cmd_struct);
		free_2d_arr(*env);
		exit(exit_code);
	}
}

void	execute_cmd(t_data **cmd_struct, t_data *cmd, char ***env)
{
	if ((!ft_strncmp(cmd->command, "echo", 4)
			&& ft_strlen(cmd->command) == 4))
		builtin_echo(cmd);
	else if ((!ft_strncmp(cmd->command, "env", 3)
			&& ft_strlen(cmd->command) == 3))
		builtin_env(*env);
	else if ((!ft_strncmp(cmd->command, "unset", 5)
			&& ft_strlen(cmd->command) == 5))
		builtin_unset(cmd, *env);
	else if ((!ft_strncmp(cmd->command, "export", 6)
			&& ft_strlen(cmd->command) == 6))
		builtin_export(cmd, env);
	else if ((!ft_strncmp(cmd->command, "cd", 2)
			&& ft_strlen(cmd->command) == 2))
		builtin_cd(cmd, env);
	else if ((!ft_strncmp(cmd->command, "pwd", 3)
			&& ft_strlen(cmd->command) == 3))
		builtin_pwd();
	else if ((!ft_strncmp(cmd->command, "exit", 4)
			&& ft_strlen(cmd->command) == 4))
		builtin_exit(cmd);
	else
		non_builtin(cmd, *env);
	check_pid(cmd_struct, cmd, env);
}

void	wait_pid(t_data **cmd)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (cmd[i])
	{
		if (cmd[i + 1])
			waitpid(cmd[i]->pid, NULL, 0);
		else
		{
			waitpid(cmd[i]->pid, &status, 0);
			if (WIFEXITED(status))
			{
				g_exit_code = WEXITSTATUS(status);
				if (!g_exit_code)
					g_exit_code = cmd[i]->exit;
				return ;
			}
		}
		i++;
	}
}

void	run_command(t_data **cmd_struct, t_data *cmd, char ***env, int *fd)
{
	set_fd_stdio(fd);
	if (redir_set_fd(cmd))
		execute_cmd(cmd_struct, cmd, env);
	close_fd_stdio(fd);
}

void	exec_main(t_data **cmd, char ***env)
{
	int	(*_pipe)[2];
	int	fd[2];
	int	i;

	signal(SIGQUIT, signal_handler);
	if (check_heredoc(cmd))
		return ;
	alloc_pipe(cmd, &_pipe);
	i = -1;
	while (cmd[++i])
	{
		if (!is_builtin_cmd(cmd[i]->command) || i > 0 || cmd[i + 1])
			cmd[i]->pid = fork();
		else
			cmd[i]->pid = PARENTS;
		if (cmd[i]->pid == CHILD || cmd[i]->pid == PARENTS)
		{
			set_fd_close_pipe(cmd, &_pipe, i);
			run_command(cmd, cmd[i], env, fd);
		}
	}
	close_pipe(cmd, &_pipe);
	free((*_pipe));
	wait_pid(cmd);
}
