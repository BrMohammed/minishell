/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_data02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:16:51 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/12 21:19:46 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*if (data[var->j] == '?') =>flage chek*/
void	make_the_key(char *data, t_dolar *var)
{
	var->key = ft_strdup("");
	var->temp = ft_strdup("");
	if (data[var->j] == '?')
	{
		free(var->temp);
		var->temp = NULL;
		var->temp = ft_itoa(g_global->g_flags);
	}
	else
		if_dolar_in_env(data, var);
	free(var->key);
}

void	begin_dolar(char *data, t_dolar *var)
{
	var->key_ex = NULL;
	make_the_key(data, var);
	if (var->temp == NULL)
	{
		var->e = ft_strjoin(var->e, "");
		var->temp = NULL;
	}
}

void	if_dolar_in_env(char *data, t_dolar *var)
{
	int	i;

	while (data[var->j] && data[var->j] != '$'
		&& ((data[var->j] >= 'a' && data[var->j] <= 'z')
			|| (data[var->j] >= 'A' && data[var->j] <= 'Z')
			|| (data[var->j] >= '0' && data[var->j] <= '9')
			|| (data[var->j] == '-') || data[var->j] == 32))
	{
		var->temp[0] = data[var->j];
		var->key = ft_strjoin(var->key, var->temp);
		var->j++;
	}
	var->j--;
	var->key_ex = strdup(var->key);
	var->key = ft_strjoin(var->key, "=");
	free(var->temp);
	var->temp = NULL;
	i = 0;
	while (g_global->envp[i] && var->temp == NULL)
	{
		var->temp = ft_strnstr(g_global->envp[i], var->key,
				ft_strlen(var->key));
		i++;
	}
}
