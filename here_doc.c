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

void handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
    exit(1);
}

int	heredoc(char *file)
{
	char	r[10240];
	char	*inputs;
	int fd_herd[2];

	int id ;
	int error;
	inputs = malloc(1);
	inputs[0] = '\0';
	r[0] = '\0';
	pipe(fd_herd);
	signal(SIGINT, SIG_IGN);
	id = fork();
	if(id == 0)
	{
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
	else
		close(fd_herd[1]);
	waitpid(id, &g_global->g_flags, 0);
	g_global->g_flags = WEXITSTATUS(g_global->g_flags);
	if(g_global->g_flags == 1)
		g_global->error_her = 1;
	return(fd_herd[0]);
}
