/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:01:10 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/12 21:12:14 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_expand(t_template *lst)
{
	t_template	*temp;

	temp = lst;
	while (lst)
	{
		if (((t_expand_data *)lst->content)->expan_data[0] != '\0')
			free(((t_expand_data *)lst->content)->expan_data);
		free(lst->content);
		lst = lst->next;
		free(temp);
		temp = lst;
	}
	free(lst);
}

void	free_der(t_template *lst)
{
	t_template	*temp;

	temp = lst;
	while (lst)
	{
		if (((t_derections *)lst->content)->expand)
			free_expand(((t_derections *)lst->content)->expand);
		free(((t_derections *)lst->content)->file);
		free(lst->content);
		lst = lst->next;
		free(temp);
		temp = lst;
	}
	free(lst);
}

void	free_text(t_template *lst)
{
	t_template	*temp;

	temp = lst;
	while (lst)
	{
		if (((t_text *)lst->content)->expand)
			free_expand(((t_derections *)lst->content)->expand);
		free(((t_text *)lst->content)->data);
		free(lst->content);
		lst = lst->next;
		free(temp);
		temp = lst;
	}
	free(lst);
}

void	free_tree(t_template *lst)
{
	t_template	*temp;

	temp = lst;
	while (lst)
	{	
		if (((t_Mlist *)lst->content)->text)
			free_text(((t_Mlist *)lst->content)->text);
		if (((t_Mlist *)lst->content)->derections)
			free_der(((t_Mlist *)lst->content)->derections);
		free(lst->content);
		lst = lst->next;
		free(temp);
		temp = lst;
	}
	free(lst);
}
