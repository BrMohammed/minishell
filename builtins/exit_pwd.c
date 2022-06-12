/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 02:36:03 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/12 04:51:04 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	args_error(char *c, int false, char *name)
{
	if (c[0] == '-')
	{
		write(2, name, ft_strlen(name));
		write(2, ": `", 3);
		write(2, &c[0], 1);
		write(2, &c[1], 1);
		write(2, "': put commend without option\n", 30);
		g_global->g_flags = 1;
		return (1);
	}
	else if (false == 1)
	{
		write(2, name, ft_strlen(name));
		write(2, ": `", 3);
		write(2, c, ft_strlen(c));
		write(2, "': put commend without args \n", 29);
		g_global->g_flags = 1;
		return (1);
	}
	return (0);
}

/*************** --  exit -- ******************/
void	exitm(char **c)
{
	int	error;

	error = 0;
	printf("exit\n");
	if (c[1])
		error = args_error(c[1], 1, "exit");
	if (error == 0)
		exit(g_global->g_flags);
	else
	{
		g_global->g_flags = 1;
		exit(g_global->g_flags);
	}
}

/*************** --  pwd -- ******************/

void	shearch_and_print(void)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (g_global->envp[y] != NULL)
	{
		if (ft_strncmp(g_global->envp[y], "PWD", 3) == 0)
			break ;
		y++;
	}
	if (g_global->envp[y] != NULL)
	{
		while ((g_global->envp[y][i] != '='))
			i++;
		if (g_global->envp[y][i] == '=')
		{
			while (g_global->envp[y][i + 1])
			{
				printf("%c", g_global->envp[y][i + 1]);
				i++;
			}
		}
		printf("\n");
	}
}

void	pwd(char **c, int fd, int false)
{
	int	error;

	error = 0;
	if (c[1])
		error = args_error(c[1], 0, "pwd");
	if (error == 0)
	{
		if (false == 1)
			dup2(fd, 1);
		shearch_and_print();
	}
	if (false == 1)
	{
		if (error == 0)
			g_global->g_flags = 0;
		exit(g_global->g_flags);
	}
	if (error == 0)
			g_global->g_flags = 0;
}
