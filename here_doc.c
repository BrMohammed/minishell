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

int	heredoc(char *file)
{
	char	r[10240];
	int		error;
	char	*inputs;
	int fd_herd[2];

	inputs = malloc(1);
	inputs[0] = '\0';
	r[0] = '\0';
	pipe(fd_herd);
	while (ft_strcmp(file, r) != -10)
	{
		inputs = ft_strjoin(inputs, r);
		write(1, "> ", 2);
		error = read(0, r, 10240);
		r[error] = '\0';
	}
	ft_putstr_fd(inputs, fd_herd[1]);
	free(inputs);
	close(fd_herd[1]);
	return(fd_herd[0]);
}
