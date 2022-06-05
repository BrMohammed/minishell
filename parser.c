# include "minishell.h"

t_template *Makelist(t_lexer *lexer, t_template **list)
{
	t_token *token;
	t_template *text; // leaks?
	t_template *derections; // leaks?
	int i = 0;
	int i2 = 0;
	char *temp2;
	int temp;
	
	
	token = GetNextToken(lexer); //<<<<< token have avery time type and value
	if(token->type == TYPE_EOF)
	{
		free(token);
		return(0);
	}
	while(token->type != TYPE_EOF)
	{
		text = NULL;
		derections = NULL;
		if (token->type == TYPE_PIPE)
		{
			i++;
			lstadd_back(&text, new_template((void*)new_text(token->value,token->type,i)));
			free(token);
			token = GetNextToken(lexer);
		}
		while (token->type != TYPE_PIPE && token->type != TYPE_EOF)
		{
			if(token->type == TYPE_TEXT || token->type == TYPE_ERROR || token->type == TYPE_QUOTE)
			{
				i++;
				lstadd_back(&text, new_template((void*)new_text(token->value,token->type,i)));
				free(token);
				token = GetNextToken(lexer);
			}
			else if(token->type == TYPE_DLredirection || token->type == TYPE_DRredirection || token->type == TYPE_Lredirection || token->type == TYPE_Rredirection)
			{
				i++;
				temp = token->type;
				free(token);
				token = GetNextToken(lexer);
				if(token->type != TYPE_EOF)
					temp2 = ft_strdup(token->value);
				free(token);
				if(token->type == TYPE_EOF)
				{
					temp2 = malloc(1);
					temp2[0] = '\0';
				}
				lstadd_back(&derections,new_template((void*)new_derections(temp2,temp,i)));
				free(temp2);
				token = GetNextToken(lexer);
			}
		}
		free(token);
		lstadd_back(list,new_template((void*)new_list(text,derections,i2)));
		i2++;
	}
	return(*list);
}

void *minishell(char* all)
{
	
	t_lexer *lexer;
	t_template *list;
	t_template *error;
	
	list = NULL;
	lexer = init_lexer(all);
	list = Makelist(lexer,&list);
	free(lexer);
	error = list;
	if(error)
	{
		if(RMlist(error) == 1)
		{
			free(list);
			free(list->content);
			return(0);
		}
	}
	if(list)
		pMlist(list);
	return(0);
}