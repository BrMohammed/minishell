/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 04:21:19 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/12 05:09:14 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fd_of_redir(t_template	*tmp, int *fd, int *interpted)
{
	generate_rederaction(((t_derections *)tmp->content)->type, tmp);
	if (((t_derections *)tmp->content)->file != NULL
		&& ((t_derections *)tmp->content)->type == TYPE_Lredirection)
		fd[0] = ((t_derections *)tmp->content)->fd;
	if (fd[0] == -1 || fd[1] == -1)
		*interpted = 1;
	if (*interpted != 1 && ((t_derections *)tmp->content)->file != NULL
		&& (((t_derections *)tmp->content)->type == TYPE_Rredirection
			|| ((t_derections *)tmp->content)->type == TYPE_DRredirection))
		fd[1] = ((t_derections *)tmp->content)->fd;
}
