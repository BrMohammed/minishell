/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 05:12:09 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/14 06:07:18 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*allocation_for_fd(void)
{
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 3);
	fd[2] = '\0';
	fd[1] = 0;
	fd[0] = 0;
	return (fd);
}

int	*out_derections(t_template *lst, int *interpted)
{
	t_template	*tmp;
	int			i;
	int			*fd;
	int			error;

	i = 0;
	fd = allocation_for_fd();
	tmp = lst;
	error = 0;
	while (lst && *interpted != 1)
	{
		if (((t_derections *)lst->content)->file != NULL
			&& ((t_derections *)lst->content)->type == TYPE_DLredirection)
			fd[0] = heredoc(((t_derections *)lst->content)->file, interpted);
		lst = lst->next;
	}
	while (tmp && *interpted != 1)
	{
		fd_of_redir(tmp, fd, interpted, &error);
		if (error == 1)
			break ;
		tmp = tmp->next;
	}
	return (fd);
}

void	piepe_exist_ans_der(int pipe_exist, t_pipeline *var,
	t_pmlist *pmlist_var, t_template *lst)
{
	var->i = 0;
	pmlist_var->enter_built = 0;
	if (((t_Mlist *)lst->content)->derections)
		var->fd_der = out_derections(((t_Mlist *)lst->content)->derections,
				&var->interpted);
	else
		var->fd_der = allocation_for_fd();
	if (lst->next != NULL)
		pipe(var->fd);
	if (pipe_exist == 0 && pmlist_var->c != NULL && var->fd_der[1] != -1
		&& var->fd_der[0] != -1 && var->interpted != 1)
		pmlist_var->enter_built = all_builtins(pmlist_var->c,
				pipe_exist, var->fd[1], var);
}

void	in_childe(t_template *lst, t_pmlist *pmlist_var,
	t_pipeline *var, int pipe_exist)
{
	if (var->interpted == 1)
		exit(1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	duplicate(var->fd_der, pmlist_var->lastfd, lst, var->fd);
	if (pipe_exist == 1 && pmlist_var->c != NULL && var->interpted != 1)
		pmlist_var->enter_built = all_builtins(pmlist_var->c,
				pipe_exist, var->fd[1], var);
	if (pmlist_var->enter_built == 0 && var->interpted != 1)
	{
		if (execve(pmlist_var->path, &pmlist_var->c[0], g_global->envp) == -1
			&& pmlist_var->c[0] != NULL)
		{
			write(2, "minishell: ", 10);
			write(2, pmlist_var->c[0], ft_strlen(pmlist_var->c[0]));
			write(2, ": command not found\n", 20);
			exit(127);
		}
	}
}

int	pipeline(t_template *lst, t_pmlist *pmlist_var,
		t_pipeline *var, int pipe_exist)
{
	piepe_exist_ans_der(pipe_exist, var, pmlist_var, lst);
	if (pmlist_var->enter_built == 0 && var->interpted != 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		var->id = fork();
		if (var->id == 0)
			in_childe(lst, pmlist_var, var, pipe_exist);
	}
	close_parent(var, &pmlist_var->lastfd, lst);
	free(var->fd_der);
	return (pmlist_var->lastfd);
}
