/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:05:21 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/13 21:56:24 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_data(char *e, t_template **expand, int branch, t_template **text)
{
	t_template	*temp00;

	temp00 = NULL;
	if (e[0] != '\0')
	{
		temp00 = *expand;
		if (temp00)
		{
			while (temp00->next != NULL)
				temp00 = temp00->next;
		}
		((t_expand_data *)temp00->content)->expan_data = ft_strdup(e);
	}
	if (branch == TEXT)
		((t_text *)(*text)->content)->expand = *expand;
	else if (branch == DERECYION)
		((t_derections *)(*text)->content)->expand = *expand;
}

void	quat_skip(char *quat, char data, char **e)
{
	char	*temp;

	temp = malloc(2);
	temp[0] = '\0';
	temp[1] = '\0';
	if ((*quat == '\'' && data == '\'') || (*quat == '"' && data == '"'))
		*quat = '\0';
	else if (data == '\'' && *quat != '"')
		*quat = '\'';
	else if (data == '"' && *quat != '\'')
		*quat = '"';
	else
	{
		temp[0] = data;
		*e = ft_strjoin(*e, temp);
	}
	free(temp);
}

int	dolar(char *data, t_dolar *var)
{
	var->i++;
	var->j = var->i;
	begin_dolar(data, var);
	if (var->temp != NULL)
	{
		detect_dolar(var);
		free(var->temp);
		free(var->key);
		free(var->key_ex);
	}
	var->i = var->j;
	return (var->i);
}

/*else if (data_c == '$' && var->quat == '\'') 
  =>when singelquet and dolar exest sqiping the key*/
/*else if (data_c == '$') =>dolar in text or inter of doublequet*/
void	search_in_data(t_dolar *var, char data_c, char *data)
{
	char	*temp;

	temp = ft_strdup("");
	if (data_c != '$')
		quat_skip(&var->quat, data_c, &var->e);
	else if (data_c == '$' && var->quat == '\'')
	{
		temp[0] = data_c;
		var->e = ft_strjoin(var->e, temp);
	}
	else if (data_c == '$')
		var->i = dolar(data, var);
	free(temp);
	temp = NULL;
}

void	make_key_of_dolar(char *data, t_template **text, int branch)
{
	t_dolar	var;

	var.i = 0;
	var.e = ft_strdup("");
	var.expand = NULL;
	var.quat = 0;
	lstadd_back(&var.expand, new_template(new_expand("", "")));
	while (var.i <= (int)ft_strlen(data))
	{
		search_in_data(&var, data[var.i], data);
		var.i++;
	}
	expand_data(var.e, &var.expand, branch, text);
	free(var.e);
}
