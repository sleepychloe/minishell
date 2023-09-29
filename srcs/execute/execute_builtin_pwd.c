/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:57:06 by yhwang            #+#    #+#             */
/*   Updated: 2023/09/18 05:14:32 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	builtin_pwd(void)
{
	char	buf[1024];

	getcwd(buf, sizeof(buf));
	if (errno == ERANGE)
	{
		stderr_msg("minishell: pwd: cannot access directory: ");
		stderr_msg("No such file or directory\n");
	}
	else
		printf("%s\n", buf);
}
