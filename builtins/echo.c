/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 02:30:46 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/14 04:05:23 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	nl_not_exist(int *nl_exist, char **c, int *i)
{
	int	y;

	if (c[1][0] == '-' && *nl_exist == 1)
	{
		y = 1;
		while (c[1][y] && c[1][y] == 'n')
			y++;
		if (c[1][y] == '\0' && c[1][1] == 'n')
		{
			*nl_exist = 0;
			*i = *i + 1;
		}
	}
}

void	nl__exist(int nl_exist, int *skip, char *c, t_pipeline *var)
{
	int	y;

	if (c != NULL)
	{
		if (nl_exist == 0)
		{
			if (c[0] == '-' && *skip == 1)
			{
				y = 1;
				while (c[y] && c[y] == 'n')
					y++;
				if (c[y] != '\0')
					skip = 0;
			}
			else
				skip = 0;
			if (skip == 0 && c != NULL)
				write(var->fd_der[1], c, ft_strlen(c));
		}
		else
			write(var->fd_der[1], c, ft_strlen(c));
	}
}

void	redir_or_pipe(int pipe_exist, int fd, t_pipeline *var)
{
	if (pipe_exist == 1 && var->fd_der[1] != 0)
	{
		dup2(var->fd_der[1], 1);
		var->fd_der[1] = 1;
	}
	else if (var->fd_der[1] == 0)
		var->fd_der[1] = 1;
	else if (pipe_exist == 1)
		dup2(fd, 1);
}

void	echo(char **c, int fd, int pipe_exist, t_pipeline *var)
{
	int	i;
	int	nl_exist;
	int	skip;

	i = 0;
	nl_exist = 1;
	skip = 1;
	redir_or_pipe(pipe_exist, fd, var);
	while (c[i + 1])
	{
		nl_not_exist(&nl_exist, c, &i);
		nl__exist(nl_exist, &skip, c[i + 1], var);
		i++;
		if (c[i + 1])
			write(var->fd_der[1], " ", 1);
	}
	if (nl_exist == 1)
		write(var->fd_der[1], "\n", 1);
	if (pipe_exist == 1)
	{
		g_global->g_flags = 0;
		exit(0);
	}
	else
		g_global->g_flags = 0;
}
