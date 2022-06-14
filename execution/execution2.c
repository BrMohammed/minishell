/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 04:21:19 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/14 22:20:47 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fd_of_redir(t_template	*lst, int *error, int *interpted)
{
	t_template	*tmp;

	tmp = lst;
	while (lst && *interpted != 1)
	{
		if (((t_derections *)lst->content)->file != NULL
			&& ((t_derections *)lst->content)->type == TYPE_DLredirection)
			((t_derections *)lst->content)->fd = heredoc(((t_derections *)lst
						->content)->file, interpted);
		lst = lst->next;
	}
	generate_rederaction(((t_derections *)tmp->content)->type, tmp, error);
}
