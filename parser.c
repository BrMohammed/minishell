# include "minishell.h"

void der_or_text(t_Makelist *var,t_lexer *lexer)
{
	if(var->token->type == TYPE_TEXT || var->token->type == TYPE_ERROR || var->token->type == TYPE_QUOTE)
	{
		var->i++;
		lstadd_back(&var->text, new_template((void*)new_text(var->token->value,var->token->type,var->i)));
		free(var->token);
		var->token = GetNextToken(lexer);
	}
	else if(var->token->type == TYPE_DLredirection || var->token->type == TYPE_DRredirection || var->token->type == TYPE_Lredirection || var->token->type == TYPE_Rredirection)
	{
		var->i++;
		var->temp = var->token->type;
		free(var->token);
		var->token = GetNextToken(lexer);
		if(var->token->type != TYPE_EOF)
			var->temp2 = ft_strdup(var->token->value);
		free(var->token);
		if(var->token->type == TYPE_EOF)
		{
			var->temp2 = malloc(1);
			var->temp2[0] = '\0';
		}
		lstadd_back(&var->derections,new_template((void*)new_derections(var->temp2,var->temp,var->i)));
		free(var->temp2);
		var->token = GetNextToken(lexer);
	}
}

void Makelist(t_lexer *lexer, t_template **list)
{
	t_Makelist var;

	var.i = 0;
	var.i2 = 0;
	var.token = GetNextToken(lexer);
	if(var.token->type == TYPE_EOF)
		free(var.token);
	while(var.token->type != TYPE_EOF || var.token->value != NULL)
	{
		var.text = NULL;
		var.derections = NULL;
		if (var.token->type == TYPE_PIPE)
		{
			var.i++;
			lstadd_back(&var.text, new_template((void*)new_text(var.token->value,var.token->type,var.i)));
			free(var.token);
			var.token = GetNextToken(lexer);
		}
		while (var.token->type != TYPE_PIPE && var.token->type != TYPE_EOF)
			der_or_text(&var,lexer);
		lstadd_back(list,new_template((void*)new_list(var.text,var.derections,var.i2)));
		var.i2++;
	}
	free(var.token);
}

void *minishell(char* all)
{
	
	t_lexer *lexer;
	t_template *list;
	t_template *error;
	
	list = NULL;
	lexer = init_lexer(all);
	Makelist(lexer,&list);
	free(lexer);
	error = list;
	if(error)
	{
		if(RMlist(error) == 1)
		{		
			free_tree(list);
			return(0);
		}
	}
	if(list)
		pMlist(list);
	free_tree(list);
	return(0);
}
