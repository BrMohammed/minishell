/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:25:16 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/14 22:25:31 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_syntax_error(char *t_temp)
{
	printf("minishael :syntax error near unexpected token '%s'\n",
		t_temp);
	g_global->g_flags = 258;
}
