/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:19:21 by brmohamm          #+#    #+#             */
/*   Updated: 2022/02/07 19:21:06 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	creat_fille(char *argv)
{
	int	output;

	output = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output == -1)
	{
		perror(argv);
	}
	else
	{
		dup2(output, 1);
		close(output);
	}
}

void	open_file(char **argv, int last)
{
	int	input;

	input = open(argv[1], O_RDWR);
	if (input == -1)
	{
		perror(argv[1]);
		input = open(argv[last], O_RDWR | O_CREAT, 0777);
		dup2(input, 0);
		close(input);
	}
	else
	{
		dup2(input, 0);
		close(input);
	}
}
