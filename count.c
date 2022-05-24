/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:33:19 by brmohamm          #+#    #+#             */
/*   Updated: 2022/02/07 19:21:10 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	count_continue(char **argv, int fals, int *i)
{
	while (argv[*i] != NULL)
		*i = *i + 1;
	if (fals == 0)
		*i = *i - 4;
	else
		*i = *i - 3 ;
}

int	**count(char **argv, int *i, int fals)
{
	int	t;
	int	**fd;

	t = 0;
	count_continue(argv, fals, i);
	fd = (int **)malloc(sizeof(int *) * (*i + 1));
	fd[*i] = NULL;
	if (!fd)
		return (0);
	while (t < *i)
	{
		fd[t] = (int *)malloc(sizeof(int) * 2 + 1);
		if (!fd[t])
			return (0);
		fd[t][2] = '\0';
		t++;
	}
	t = 0;
	while (t < *i)
	{
		pipe(fd[t]);
		t++;
	}
	return (fd);
}
