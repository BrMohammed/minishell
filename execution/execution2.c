/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 04:21:19 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/15 01:06:03 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	while_on_doc(t_template	*lst)
{
	int	interpted;

	interpted = 0;
	while (lst && interpted != 1)
	{
		if (((t_derections *)lst->content)->file != NULL
			&& ((t_derections *)lst->content)->type == TYPE_DLredirection)
			((t_derections *)lst->content)->fd = heredoc(((t_derections *)lst
						->content)->file, &interpted);
		lst = lst->next;
	}
	return (interpted);
}

int	erro_on_der_flag(t_template *lst)
{
	while (lst)
	{
		if (((t_derections *)lst->content)->fd == -1)
			return (1);
		lst = lst->next;
	}
	return (0);
}
