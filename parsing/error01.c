/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:21:15 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/12 23:21:55 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_type_def_left_redirection(int type, t_derections	*temp)
{
	if (type == TYPE_Lredirection)
	{
		if (temp->expand->next != NULL
			|| ((t_expand_data *)temp->expand->content)->expan_data[0] == '\0')
			ambiguous_redir(&temp->fd, temp->file);
		else
		{
			temp->fd = open(temp->file, O_RDONLY);
			if (temp->fd == -1)
				printf("minishell: %s: No such file or directory\n", temp->file);
		}
	}
}

char	*redir_type(t_template *lst)
{
	char	*t_temp;

	if (((t_derections *)lst->content)->type == TYPE_Lredirection)
		t_temp = "<";
	if (((t_derections *)lst->content)->type == TYPE_Rredirection)
		t_temp = ">";
	if (((t_derections *)lst->content)->type == TYPE_DLredirection)
		t_temp = "<<";
	if (((t_derections *)lst->content)->type == TYPE_DRredirection)
		t_temp = ">>";
	return (t_temp);
}
