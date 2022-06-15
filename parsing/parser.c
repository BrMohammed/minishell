/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:34:20 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/15 00:33:36 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_makelist *var)
{
	if (var->token->value != NULL)
		free(var->token->value);
	free(var->token);
}

void	type_redir(t_makelist *var, t_lexer *lexer)
{
	var->i++;
	var->temp = var->token->e_type;
	free_token(var);
	var->token = get_next_token(lexer);
	if (var->token->e_type != TYPE_EOF)
		var->temp2 = ft_strdup(var->token->value);
	if (var->token->e_type == TYPE_EOF)
	{
		var->temp2 = malloc(1);
		var->temp2[0] = '\0';
	}
	free_token(var);
	lstadd_back(&var->derections, new_template((void *)new_derections(
				var->temp2, var->temp, var->i)));
	free(var->temp2);
	var->token = get_next_token(lexer);
}

void	der_or_text(t_makelist *var, t_lexer *lexer)
{
	if (var->token->e_type == TYPE_TEXT || var->token->e_type == TYPE_ERROR
		|| var->token->e_type == TYPE_QUOTE)
	{
		var->i++;
		lstadd_back(&var->text, new_template((void *)new_text(var->token->value,
					var->token->e_type, var->i)));
		free_token(var);
		var->token = get_next_token(lexer);
	}
	else if (var->token->e_type == TYPE_DLredirection
		|| var->token->e_type == TYPE_DRredirection
		|| var->token->e_type == TYPE_Lredirection
		|| var->token->e_type == TYPE_Rredirection)
	{
		type_redir(var, lexer);
	}
}

void	makelist(t_lexer *lexer, t_template **list)
{
	t_makelist	var;

	var.token = get_next_token(lexer);
	var.i = 0;
	if (var.token->e_type == TYPE_EOF)
		return (free_token(&var));
	while (var.token->e_type != TYPE_EOF || var.token->value != NULL)
	{
		var.text = NULL;
		var.derections = NULL;
		if (var.token->e_type == TYPE_PIPE)
		{
			var.i++;
			lstadd_back(&var.text, new_template((void *)new_text(
						var.token->value, var.token->e_type, var.i)));
			free_token(&var);
			var.token = get_next_token(lexer);
		}
		while (var.token->e_type != TYPE_PIPE && var.token->e_type != TYPE_EOF)
			der_or_text(&var, lexer);
		lstadd_back(list, new_template((void *)new_list(
					var.text, var.derections, var.i2)));
		var.i2++;
	}
	free_token(&var);
}

void	*minishell(char	*all)
{
	t_lexer		*lexer;
	t_template	*list;

	list = NULL;
	lexer = init_lexer(all);
	makelist(lexer, &list);
	free(lexer);
	if (list)
		pmlist(list);
	free_tree(list);
	return (0);
}
