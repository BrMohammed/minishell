/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:21:15 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/15 00:59:31 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_of_no_der(char *file, int *error)
{
	printf("minishell: %s: No such file or directory\n", file);
	g_global->g_flags = 1;
	*error = 1;
}

void	if_type_def_left_redirection_and_dr(int type,
			t_derections	*temp, int *error)
{
	if (type == TYPE_DRredirection && *error != 1)
	{
		if (temp->expand->next != NULL
			|| ((t_expand_data *)temp->expand->content)->expan_data[0] == '\0')
			*error = ambiguous_redir(&temp->fd, temp->file);
		else if (ft_strcmp(temp->file, ".") == 0)
			print_error_of_generate_rederaction(temp, error);
		else
			temp->fd = open(((t_expand_data *)temp->expand->content)
					->expan_data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (type == TYPE_Lredirection && *error != 1)
	{
		if (temp->expand->next != NULL
			|| ((t_expand_data *)temp->expand->content)->expan_data[0] == '\0')
			*error = ambiguous_redir(&temp->fd, temp->file);
		else
		{
			temp->fd = open(temp->file, O_RDONLY);
			if (temp->fd == -1)
				print_of_no_der(temp->file, error);
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

void	print_error_of_rtext(void)
{
	printf("minishael :syntax error near unexpected token '%s'\n", "|");
	g_global->g_flags = 258;
}

void	print_error_of_generate_rederaction(t_derections	*temp, int *error)
{
	printf("minishell: .: Is a directory\n");
	(temp)->fd = -1;
	*error = 1;
}
