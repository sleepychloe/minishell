/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:52:37 by yhwang            #+#    #+#             */
/*   Updated: 2023/08/23 02:29:00 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_exit_code;

char	**alloc_env(char **env)
{
	char	**arr_env;
	int		i;

	arr_env = (char **)ft_calloc(sizeof(char *), 2);
	if (!arr_env)
		return (printf("%sError: malloc error%s\n", RED, BLACK), NULL);
	i = -1;
	while (env[++i])
	{
		arr_env = ft_realloc(arr_env, sizeof(char *) * (i + 1),
				sizeof(char *) * (i + 2));
		arr_env[i] = strdup(env[i]);
		if (!arr_env[i])
		{
			printf("%sError: malloc error%s\n", RED, BLACK);
			return (free_2d_arr(env), NULL);
		}
	}
	return (arr_env);
}

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

int	minishell_main(t_data **cmd, char **env)
{
	char	*rdline;

	while (1)
	{
		/* detect signal */
		signal_detect();
		/* alloc cmd */
		cmd = ft_calloc(sizeof(t_data *), 2);
		/* error check: malloc */
		if (!cmd)
			return (printf("%sError: malloc error%s\n", RED, BLACK), 1);
		/* read command */
		rdline = readline("\x1b[36mminishell$\x1b[0m ");
		/* when rdline is NULL: ctrl - D */
		if (!rdline)
		{
			/* print exit and free cmd structure */
			printf("exit\n");
			return (free_cmd(cmd), 1);
		}
		add_history(rdline);
		/* start parsing */
		cmd = parse(cmd, env, rdline);
		/* check if any error happened and free rdline if there was error
			and then while loop will be repeated
			: if any error has happened during parsing,
			cmd is freed and NULL was returned */
		if (!cmd)
		{
			free(rdline);
			continue ;
		}
		/* execute command */
		exec_main(cmd, env);
		/* free rdline and cmd struct for next command */
		free(rdline);
		free_cmd(cmd);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	**cmd;

	(void)argv;
	/* error check: argument */
	if (argc != 1)
		return (printf("%sArgument error\nUseage: ./minishell%s\n",
				RED, BLACK), 1);
	/* alloc env variable */
	env = alloc_env(env);
	/* error check: malloc */
	if (!env)
		return (1);
	/* print our minishell header */
	minishell_header();
	cmd = NULL;
	/* normal operation
		: if any error happened, free env variable and return 1 */
	if (minishell_main(cmd, env))
		return (free_2d_arr(env), 1);
	/* free: env variable */
	free_2d_arr(env);
	return (0);
}
