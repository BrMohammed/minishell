/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:56:46 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/14 00:18:50 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_d(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	lop_onarg(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (is_d(c[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}