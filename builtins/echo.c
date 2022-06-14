/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 02:30:46 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/14 21:02:10 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nl_not_exist(int *nl_exist, char *c, int *i)
{
	int	y;

	if (c[0] == '-')
	{
		y = 1;
		while (c[y] && c[y] == 'n')
			y++;
		if (c[y] == '\0')
		{
			*nl_exist = 0;
			*i = *i + 1;
			return (0);
		}
	}
	return (1);
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

void	while_on_newlin(char **c, int *nl_exist, int *i)
{
	while (c[*i + 1])
	{
		if (nl_not_exist(nl_exist, c[*i + 1], i) == 1)
			break ;
	}
}

void	echo(char **c, int fd, int pipe_exist, t_pipeline *var)
{
	int	i;
	int	nl_exist;

	i = 0;
	nl_exist = 1;
	redir_or_pipe(pipe_exist, fd, var);
	while_on_newlin(c, &nl_exist, &i);
	while (c[i + 1])
	{
		if (c[i + 1] != NULL)
			write(var->fd_der[1], c[i + 1], ft_strlen(c[i + 1]));
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
