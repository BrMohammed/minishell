/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:03:07 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/12 21:12:14 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand_data	*new_expand(char *expand_data, char *key)
{
	t_expand_data	*expand;

	expand = malloc(sizeof(t_expand_data));
	expand->expan_data = expand_data;
	expand->key = key;
	return (expand);
}

void	lstadd_back(t_template **lst, t_template *new)
{
	t_template	*temp;

	if (*lst)
	{	
		temp = lstlast(*lst);
		new->prev = temp;
		temp->next = new;
	}
	else
		*lst = new;
}

t_template	*lstlast(t_template *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

t_template	*new_template(void *content)
{
	t_template	*index;

	index = (t_template *)malloc(sizeof(t_template));
	if (!index)
		return (NULL);
	index->content = content;
	index->next = NULL;
	index->prev = NULL;
	return (index);
}

void	lstiter(t_template *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
