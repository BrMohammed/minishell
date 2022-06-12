/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:02:54 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/12 21:03:00 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**path_finder_half(char **path, char **paths02, char **envp)
{
	int		i;
	char	**paths03;

	i = 0;
	while (envp[i] && *path == NULL)
		*path = ft_strnstr(envp[i++], "PATH=", 5);
	if (*path != NULL)
	{
		paths02 = ft_split(*path, ':');
		i = 0;
		while (paths02[i])
			i++;
		paths03 = (char **)malloc(sizeof(char *) * (i + 1));
		paths03[i] = NULL;
		i = 0;
		while (paths02[i])
		{
			paths03[i] = ft_strjoin(paths02[i], "/");
			i++;
		}
		free(paths02);
	}
	else
		paths03 = NULL;
	return (paths03);
}

void	link_ready(int if_access, char **path, char **c)
{
	int		i;
	char	*temp;

	i = 0;
	if (if_access == -1)
	{
		while (c[0][i])
			i++;
		temp = malloc(i + 1);
		temp[i] = '\0';
		i = 0;
		while (c[0][i])
		{
			temp[i] = c[0][i];
			i++;
		}
		*path = ft_strjoin(temp, "");
		if_access = access(*path, F_OK);
		if (if_access == -1)
		{
			free(*path);
			*path = NULL;
		}
	}
}

int	midel_of_path(char **paths03, char **path, char *c, int *if_access)
{
	int		i;

	i = 0;
	if (*paths03 != NULL)
	{
		while (paths03[i] && *if_access == -1)
		{
			*path = ft_strjoin(paths03[i], &c[0]);
			*if_access = access(*path, F_OK);
			if (*if_access == -1)
			{
				free(*path);
				*path = NULL;
			}
			i++;
		}
	}
	return (i);
}

void	path_finder(char **path, char **c, char **envp)
{
	int		i;
	int		if_access;
	char	**paths02;
	char	**paths03;

	if_access = -1;
	paths02 = NULL;
	paths03 = path_finder_half(path, paths02, envp);
	if (paths03 != NULL)
	{
		i = midel_of_path(paths03, path, c[0], &if_access);
		link_ready(if_access, path, c);
		while (paths03[i])
		{
			free(paths03[i]);
			i++;
		}
		free(paths03);
	}
}
