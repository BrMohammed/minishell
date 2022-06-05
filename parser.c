# include "minishell.h"

t_template *Makelist(t_lexer *lexer, t_template **list)
{
	t_token *token;
	t_template *text; // leaks?
	t_template *derections; // leaks?
	int i = 0;
	int i2 = 0;
	
	token = GetNextToken(lexer); //<<<<< token have avery time type and value
	if(token->type == TYPE_EOF)
		return(0);
	while(token->type != TYPE_EOF)
	{
		text = NULL;
		derections = NULL;
		if (token->type == TYPE_PIPE)
		{
			i++;
			lstadd_back(&text, new_template((void*)new_text(token->value,token->type,i)));
			token = GetNextToken(lexer);
		}
		while (token->type != TYPE_PIPE && token->type != TYPE_EOF)
		{
			if(token->type == TYPE_TEXT || token->type == TYPE_ERROR || token->type == TYPE_QUOTE)
			{
				i++;
				lstadd_back(&text, new_template((void*)new_text(token->value,token->type,i)));
				token = GetNextToken(lexer);
			}
			else if(token->type == TYPE_DLredirection || token->type == TYPE_DRredirection || token->type == TYPE_Lredirection || token->type == TYPE_Rredirection)
			{
				i++;
				int temp = token->type;
				token = GetNextToken(lexer);
				char *temp2 = token->value;
				if(token->type == TYPE_EOF)
				{
					temp2 = malloc(1);
					temp2[0] = '\0';
				}
				lstadd_back(&derections,new_template((void*)new_derections(temp2,temp,i)));
				token = GetNextToken(lexer);
			}
		}
		lstadd_back(list,new_template((void*)new_list(text,derections,i2)));
		
		i2++;
	}
	free(token);
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
			return(0);
	}
	if(list)
		pMlist(list);
	free(list);
	return(0);
}