/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:34:30 by brmohamm          #+#    #+#             */
/*   Updated: 2022/02/07 19:20:51 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	heredoc(char *argv)
{
	char	r[10240];
	int		error;
	char	*inputs;
	int		f;

	inputs = malloc(1);
	inputs[0] = '\0';
	r[0] = '\0';
	while (ft_strcmp(argv, r) != -10)
	{
		inputs = ft_strjoin(inputs, r);
		write(1, "heredoc> ", 9);
		error = read(0, r, 10240);
		r[error] = '\0';
	}
	error = 0;
	f = open("here_doc", O_RDWR | O_CREAT, 0777);
	if (inputs[error])
	{
		while (inputs[error])
		{
			write(f, &inputs[error++], 1);
		}
	}
	free(inputs);
}
