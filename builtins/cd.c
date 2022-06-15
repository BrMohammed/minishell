/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 02:05:32 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/15 03:35:07 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**error_handel(char *c, char **old)
{
	DIR		*dir;
	char	**temp;

	dir = opendir(c);
	if (dir == NULL)
	{
		write(2, "minishell: cd: ", 15);
		write(2, c, ft_strlen(c));
		write(2, ": No such file or directory\n", 28);
		g_global->g_flags = 1;
		return (NULL);
	}
	closedir(dir);
	temp = (char **)malloc(sizeof(char *) * 3);
	temp[2] = NULL;
	*old = ft_strdup("OLDPWD=");
	temp[0] = ft_strdup("export");
	return (temp);
}

int	move_to_dir(char *c, t_pipeline *var)
{
	char	cwd[256];
	char	*old;
	char	**temp;

	temp = error_handel(c, &old);
	if (temp == NULL)
		return (0);
	getcwd(cwd, sizeof(cwd));
	old = ft_strjoin(old, cwd);
	temp[1] = ft_strdup(old);
	export(temp, 0, 0, var);
	free(old);
	free(temp[1]);
	chdir(c);
	old = ft_strdup("PWD=");
	getcwd(cwd, sizeof(cwd));
	old = ft_strjoin(old, cwd);
	temp[1] = ft_strdup(old);
	export(temp, 0, 0, var);
	free_table(temp);
	temp = NULL;
	free(old);
	old = NULL;
	return (0);
}

void	cd(char **c, int false)
{
	t_pipeline		var;
	int				error;

	error = 0;
	if (c[1] != NULL)
		error = move_to_dir(c[1], &var);
	else if (c[1] == NULL)
		error = move_to_dir(getenv("HOME"), &var);
	if (false == 1)
	{
		if (error == 0)
			g_global->g_flags = 0;
		exit(g_global->g_flags);
	}
	if (error == 0)
		g_global->g_flags = 0;
}
