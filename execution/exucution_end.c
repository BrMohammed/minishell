/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exucution_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 05:27:58 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/12 05:30:45 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**creat_table(t_template *lst)
{
	t_template	*temp_exp;
	int			number_of_cases;
	char		**c;

	c = NULL;
	number_of_cases = 0;
	while (lst)
	{
		temp_exp = ((t_text *)lst->content)->expand;
		while (temp_exp)
		{
			if (ft_strncmp(((t_ExpandData *)lst->content)->expan_data,
					"|", 1) != 0)
				number_of_cases++;
			temp_exp = temp_exp->next;
		}
		lst = lst->next;
	}
	if (number_of_cases != 0)
	{
		c = (char **)malloc(sizeof(char *) * (number_of_cases + 1));
		c[number_of_cases] = NULL;
	}
	return (c);
}

void	duplicate(int *fd_Der, int lastFd, t_template *lst, int *fd)
{
	if (fd_Der[0] == -1 || fd_Der[1] == -1)
		exit(1);
	if (fd_Der[0] > 0)
	{
		dup2(fd_Der[0], 0);
		close(fd_Der[0]);
	}
	else if (lastFd != -1)
	{
		dup2(lastFd, 0);
		close(lastFd);
	}
	if (fd_Der[1] > 0)
	{
		dup2(fd_Der[1], 1);
		close(fd_Der[1]);
	}
	else if (lst->next != NULL)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
	}
}

void	close_parent(t_pipeline var, int *lastFd, t_template *lst)
{
	((t_Mlist *)lst->content)->pid = var.id;
	if (*lastFd != -1)
		close(*lastFd);
	*lastFd = var.fd[0];
	if (lst->next != NULL)
		close(var.fd[1]);
	if (var.fd_Der[1] > 0)
		close(var.fd_Der[1]);
	if (var.fd_Der[0] > 0)
		close(var.fd_Der[0]);
}

int	all_builtins01(char **c, int pipe_exist, int fd)
{
	if (ft_strcmp(c[0], "export") == 0)
	{
		export(c, fd, pipe_exist);
		return (1);
	}
	if (ft_strcmp(c[0], "unset") == 0)
	{
		unset(c, pipe_exist);
		return (1);
	}
	if (ft_strcmp(c[0], "exit") == 0)
	{
		exitm(c);
		return (1);
	}
	if (ft_strcmp(c[0], "env") == 0)
	{
		envm(c, fd, pipe_exist);
		return (1);
	}
	return (0);
}

int	all_builtins(char **c, int pipe_exist, int fd)
{
	char	*temp;

	if (all_builtins01(c, pipe_exist, fd) == 1)
		return (1);
	if (ft_strcmp(c[0], "pwd") == 0)
	{
		pwd (c, fd, pipe_exist);
		return (1);
	}
	temp = ft_tolower(c[0]);
	if (ft_strcmp(temp, "echo") == 0)
	{
		echo(c, fd, pipe_exist);
		free(temp);
		return (1);
	}
	if (ft_strcmp(c[0], "cd") == 0)
	{
		cd(c, pipe_exist);
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}
