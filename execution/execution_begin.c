/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_begin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 04:55:22 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/12 05:11:36 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*   exp  for looping in the expanded link of node text*/
char	**ptext(t_template *lst)
{
	t_template	*exp;
	int			number_of_cases;
	char		**c;

	c = creat_table(lst);
	number_of_cases = 0;
	while (lst)
	{
		exp = ((t_text *)lst->content)->expand;
		while (exp)
		{
			if (ft_strncmp(
					((t_ExpandData *)exp->content)->expan_data, "|", 1) != 0)
			{
				c[number_of_cases] = ft_strdup(
						((t_ExpandData *)exp->content)->expan_data);
				number_of_cases++;
			}
			exp = exp->next;
		}
		lst = lst->next;
	}
	return (c);
}

void	while_on_wait(t_template *tmp, t_pmlist pmlist_var)
{
	while (tmp)
	{
		if (pmlist_var.enter_built == 0 && g_global->error_her == 0)
			waitpid(((t_Mlist *)tmp->content)->pid, &g_global->g_flags, 0);
		else
			waitpid(((t_Mlist *)tmp->content)->pid, NULL, 0);
		if (g_global->g_flags == 2)
			g_global->g_flags = 130;
		else if (g_global->g_flags == 3)
			g_global->g_flags = 131;
		else if (((t_Mlist *)tmp->content)->pid != 0
			&& g_global->error_her == 0)
			g_global->g_flags = WEXITSTATUS(g_global->g_flags);
		tmp = tmp->next;
	}
}

void	pmlist(t_template *lst)
{
	t_pmlist	pmlist_var;
	t_template	*tmp;

	tmp = lst;
	pmlist_var.lastFd = -1;
	while (lst)
	{
		pmlist_var.c = NULL;
		pmlist_var.path = NULL;
		if (((t_Mlist *)lst->content)->text
			|| ((t_Mlist *)lst->content)->derections)
		{
			pmlist_var.c = ptext(((t_Mlist *)lst->content)->text);
			if (pmlist_var.c != NULL)
				path_finder(&pmlist_var.path, pmlist_var.c, g_global->envp);
			pmlist_var.lastFd = pipeline(lst, &pmlist_var);
			if (pmlist_var.path != NULL)
				free(pmlist_var.path);
			if (pmlist_var.c != NULL)
				free_table(pmlist_var.c);
		}
		lst = lst->next;
	}
	while_on_wait(tmp, pmlist_var);
}
