/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 02:31:14 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/14 04:13:00 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_equal_exist(int equal_exist, t_pipeline *var, int i)
{
	if (equal_exist == 1)
	{
		write(var->fd_der[1], g_global->envp[i],
			ft_strlen(g_global->envp[i]));
		write(var->fd_der[1], "\n", 1);
	}
}

void	print_env(t_pipeline *var)
{
	int	i;
	int	y;
	int	equal_exist;

	i = 0;
	equal_exist = 0;
	while (g_global->envp[i])
	{
		y = 0;
		equal_exist = 0;
		while (g_global->envp[i][y])
		{
			if (g_global->envp[i][y] == '=' && g_global->envp[i][y + 1])
			{
				equal_exist = 1;
				break ;
			}
			y++;
		}
		if_equal_exist(equal_exist, var, i);
		i++;
	}
}

void	envm(char **c, int fd, int pipe_exist, t_pipeline *var)
{
	int	error;

	error = 0;
	if (c[1])
		error = args_error(c[1], 1, "env");
	if (error == 0)
	{
		redir_or_pipe(pipe_exist, fd, var);
		print_env(var);
	}
	if (pipe_exist == 1)
	{
		if (error == 0)
			g_global->g_flags = 0;
		exit(g_global->g_flags);
	}
	if (error == 0)
			g_global->g_flags = 0;
}
