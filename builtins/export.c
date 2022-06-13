/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 02:39:11 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/13 21:59:43 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	just_export(int fd, int false)
{
	int	i;

	i = 0;
	if (false == 1)
		dup2(fd, 1);
	while (g_global->envp[i])
	{
		print_export(g_global->envp[i]);
		i++;
	}
}

int	serch_on_env(char *c, int *error)
{
	int	i;

	i = 0;
	*error = 0;
	while (c[i] && c[i] != '=')
		i++;
	if (errorin_args(c, *error, i) == 1)
		return (1);
	if (c[i] == '\0')
	{
		i = 0;
		while (g_global->envp[i] && ft_strcmp(g_global->envp[i], c) != 0)
			i++;
		if (g_global->envp[i] != NULL)
			return (1);
	}
	else
	{
		if (replace(i, c) == 1)
			return (1);
	}
	return (0);
}

char	**add_to_table(char *c)
{
	int		i;
	char	**cr;

	i = 0;
	while (g_global->envp[i])
		i++;
	cr = (char **)malloc(sizeof(char *) * (i + 2));
	cr[i + 1] = NULL;
	i = 0;
	while (g_global->envp[i] != NULL)
	{
		cr[i] = ft_strdup(g_global->envp[i]);
		i++;
	}
	cr[i] = ft_strdup(c);
	return (cr);
}

void	add_in_export(char **c, int *error_out)
{
	char	**cr;
	int		serch;
	int		x;
	int		error;

	serch = 0;
	x = 1;
	error = 0;
	while (c[x])
	{
		cr = NULL;
		serch = serch_on_env(c[x], &error);
		if (error == 1)
			*error_out = 1;
		if (serch == 0 && *error_out == 0)
		{
			cr = add_to_table(c[x]);
			free_table(g_global->envp);
			copie_table(cr);
			free_table(cr);
			cr = NULL;
		}
		x++;
	}
}

void	export(char **c, int fd, int false)
{
	int	error;

	error = 0;
	if (c[1] == '\0')
		just_export(fd, false);
	else
		add_in_export(c, &error);
	if (false == 1)
	{
		if (error == 0)
			g_global->g_flags = 0;
		exit(g_global->g_flags);
	}
	if (error == 0)
			g_global->g_flags = 0;
}
