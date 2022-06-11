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
void free_expand(t_template *lst)
{
	t_template *temp;

	temp = lst;
	while(lst)
	{
		if(((t_ExpandData*)lst->content)->expan_data[0] != '\0')
			free(((t_ExpandData*)lst->content)->expan_data);
		free(lst->content);
		lst = lst->next;
		free(temp);
		temp = lst;
	}
	free(lst);
}
void free_der(t_template *lst)
{
	t_template *temp;

	temp = lst;
	while(lst)
	{
		if(((t_derections*)lst->content)->expand)
			free_expand(((t_derections*)lst->content)->expand);
		free(((t_derections*)lst->content)->file);
		free(lst->content);
		lst = lst->next;
		free(temp);
		temp = lst;
	}
	free(lst);
}

void free_text(t_template *lst)
{
	t_template *temp;

	temp = lst;
	while(lst)
	{
		if(((t_text*)lst->content)->expand)
			free_expand(((t_derections*)lst->content)->expand);
		free(((t_text*)lst->content)->data);
		free(lst->content);
		lst = lst->next;
		free(temp);
		temp = lst;
	}
	free(lst);
}

void free_tree(t_template *lst)
{
	t_template *temp;

	temp = lst;
	while(lst)
	{	
		if(((t_Mlist *)lst->content)->text)
		free_text(((t_Mlist *)lst->content)->text);
	if(((t_Mlist *)lst->content)->derections)
		free_der(((t_Mlist *)lst->content)->derections);
		free(lst->content);
		lst = lst->next;
		free(temp);
		temp = lst;
	}
	free(lst);
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
