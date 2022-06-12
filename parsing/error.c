/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:38:58 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/12 22:56:54 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rtext(t_template *lst)
{
	while (lst)
	{
		if ((((t_text *)lst->content)->data[0] == '|'
				&& ((t_text *)lst->content)->order == 1))
		{
			printf("minishael :syntax error near unexpected token '%s'\n", "|");
			g_global->g_flags = 258;
			return (1);
		}
		if (((t_text *)lst->content)->type == TYPE_ERROR)
		{
			printf("Syntax Error\n");
			g_global->g_flags = 1;
			return (1);
		}
		if ((((t_text *)lst->content)->data[0] == '|' && lst->next == NULL))
		{
			printf("minishael :syntax error near unexpected token '%s'\n", "|");
			g_global->g_flags = 258;
			return (2);
		}
		make_key_of_dolar(((t_text *)lst->content)->data, &lst, TEXT);
		lst = lst->next;
	}
	return (0);
}

void	ambiguous_redir(int *fd, char *file)
{
	printf("minishell: %s: ambiguous redirect\n", file);
	*fd = -1;
}

/*TYPE_DRredirection => out >>*/
void	generate_rederaction(int type, t_template *lst)
{
	t_derections	*temp;

	temp = (t_derections *)lst->content;
	if (type == TYPE_Rredirection)
	{
		if (temp->expand->next != NULL
			|| ((t_expand_data *)temp->expand->content)->expan_data[0] == '\0')
			ambiguous_redir(&(temp)->fd,
				(temp)->file);
		else
			(temp)->fd = open(((t_expand_data *)temp->expand->content)
					->expan_data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (type == TYPE_DRredirection)
	{
		if (temp->expand->next != NULL
			|| ((t_expand_data *)temp->expand->content)->expan_data[0] == '\0')
			ambiguous_redir(&temp->fd, temp->file);
		else
			temp->fd = open(((t_expand_data *)temp->expand->content)
					->expan_data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
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

int	rderections(t_template *lst)
{
	char	*t_temp;

	while (lst)
	{
		if (((t_derections *)lst->content)->type == TYPE_Lredirection)
			t_temp = "<";
		if (((t_derections *)lst->content)->type == TYPE_Rredirection)
			t_temp = ">";
		if (((t_derections *)lst->content)->type == TYPE_DLredirection)
			t_temp = "<<";
		if (((t_derections *)lst->content)->type == TYPE_DRredirection)
			t_temp = ">>";
		if (ft_strncmp(((t_derections *)lst->content)->file, "", 1) == 0
			|| ft_strncmp(((t_derections *)lst->content)->file, "|", 1) == 0
			|| ft_strncmp(((t_derections *)lst->content)->file, ">", 1) == 0
			|| ft_strncmp(((t_derections *)lst->content)->file, "<", 1) == 0)
		{
			printf("minishael :syntax error near unexpected token '%s'\n",
				t_temp);
			g_global->g_flags = 258;
			return (1);
		}
		make_key_of_dolar(((t_derections *)lst->content)->file,
			&lst, DERECYION);
		lst = lst->next;
	}
	return (3);
}

int	rmlist(t_template *lst)
{
	int	r;
	int	r2;

	while (lst)
	{
		r = 0;
		r2 = 0;
		if (((t_Mlist *)lst->content)->text)
			r = rtext(((t_Mlist *)lst->content)->text);
		if (((t_Mlist *)lst->content)->derections && r != 1 && r != 2)
			r2 = rderections(((t_Mlist *)lst->content)->derections);
		if (r == 2 & r2 == 0)
			return (1);
		lst = lst->next;
		if (r == 1 || r2 == 1)
			return (1);
	}
	return (0);
}
