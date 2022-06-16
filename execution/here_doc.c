/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 05:27:13 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/16 11:18:55 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	exit(1);
}

void	while_on_her(int *fd_herd, char *file)
{
	char	*inputs;
	char	r[10240];
	int		error;

	inputs = malloc(1);
	inputs[0] = '\0';
	r[0] = '\0';
	error = 1;
	signal(SIGINT, handler);
	close(fd_herd[0]);
	while (ft_strcmp(file, r) != -10 && error != 0)
	{
		inputs = ft_strjoin(inputs, r);
		write(1, "> ", 2);
		error = read(0, r, 10240);
		r[error] = '\0';
	}
	ft_putstr_fd(inputs, fd_herd[1]);
	free(inputs);
	close(fd_herd[1]);
	exit(0);
}

int	heredoc(char *file, int *error)
{
	int	fd_herd[2];
	int	id;

	pipe(fd_herd);
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
		while_on_her(fd_herd, file);
	else
		close(fd_herd[1]);
	waitpid(id, &g_global->g_flags, 0);
	g_global->g_flags = WEXITSTATUS(g_global->g_flags);
	if (g_global->g_flags == 1)
	{
		g_global->error_her = 1;
		*error = 1;
	}
	return (fd_herd[0]);
}
