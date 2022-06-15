/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:38:58 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/15 01:01:15 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rtext(t_template *lst, t_template *lst2)
{
	while (lst)
	{
		if ((((t_text *)lst->content)->data[0] == '|'
				&& ((t_text *)lst->content)->order == 1))
		{
			print_error_of_rtext();
			return (1);
		}
		if (((t_text *)lst->content)->type == TYPE_ERROR)
		{
			printf("Syntax Error\n");
			g_global->g_flags = 1;
			return (1);
		}
		if (((t_text *)lst->content)->data[0] == '|' && lst->next == NULL
			&& (!lst2))
		{
			print_error_of_rtext();
			return (2);
		}
		make_key_of_dolar(((t_text *)lst->content)->data, &lst, TEXT);
		lst = lst->next;
	}
	return (0);
}

int	ambiguous_redir(int *fd, char *file)
{
	printf("minishell: %s: ambiguous redirect\n", file);
	*fd = -1;
	g_global->g_flags = 1;
	return (1);
}

/*TYPE_DRredirection => out >>*/
void	generate_rederaction(int type, t_template *lst, int *error)
{
	t_derections	*temp;

	temp = (t_derections *)lst->content;
	if (type == TYPE_Rredirection && *error != 1)
	{
		if (temp->expand->next != NULL
			|| ((t_expand_data *)temp->expand->content)->expan_data[0] == '\0')
			*error = ambiguous_redir(&(temp)->fd,
					(temp)->file);
		else if (ft_strcmp(temp->file, ".") == 0)
			print_error_of_generate_rederaction(temp, error);
		else
			(temp)->fd = open(((t_expand_data *)temp->expand->content)
					->expan_data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if_type_def_left_redirection_and_dr(type, temp, error);
}

int	rderections(t_template *lst)
{
	char	*t_temp;
	int		error;
	int		interapted;

	error = 0;
	interapted = while_on_doc(lst);
	while (lst)
	{
		t_temp = redir_type(lst);
		if (ft_strncmp(((t_derections *)lst->content)->file, "", 1) == 0
			|| ft_strncmp(((t_derections *)lst->content)->file, "|", 1) == 0
			|| ft_strncmp(((t_derections *)lst->content)->file, ">", 1) == 0
			|| ft_strncmp(((t_derections *)lst->content)->file, "<", 1) == 0)
		{
			print_syntax_error(t_temp);
			return (1);
		}
		make_key_of_dolar(((t_derections *)lst->content)->file,
			&lst, DERECYION);
		generate_rederaction(((t_derections *)lst->content)->type, lst, &error);
		if (error == 1 || interapted == 1)
			return (1);
		lst = lst->next;
	}
	return (3);
}

int	rmlist(t_template *lst)
{
	int	r;
	int	r2;

	r = 0;
	r2 = 0;
	if (((t_Mlist *)lst->content)->text)
		r = rtext(((t_Mlist *)lst->content)->text,
				((t_Mlist *)lst->content)->derections);
	if (((t_Mlist *)lst->content)->derections && r != 1 && r != 2)
		r2 = rderections(((t_Mlist *)lst->content)->derections);
	if (r == 2 & r2 == 0)
		return (1);
	if (r == 1 || r2 == 1)
		return (1);
	return (0);
}
