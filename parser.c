# include "minishell.h"
# include "libft/libft.h"


t_template *Makelist(t_lexer *lexer, t_template **list,t_global *g_global)
{
	t_token *token;
	t_template *text;
	t_template *derections;
	int i = 0;
	(void)g_global;
	token = GetNextToken(lexer); //<<<<< token have avery time type and value
	if(token->type == TYPE_EOF)
		return(0);
	while(token->type != TYPE_EOF)
	{
		text = NULL;
		derections = NULL;
		while (token->type != TYPE_PIPE || token->type != TYPE_EOF || token->type != TYPE_ERROR)
		{
			if(token->type == TYPE_TEXT)
			{

				lstadd_back(&text, new_template((void*)new_text(token->value,token->type,i)));
				token = GetNextToken(lexer);
				
			}
			else if(token->type == TYPE_DLredirection || token->type == TYPE_DRredirection || token->type == TYPE_Lredirection || token->type == TYPE_Rredirection)
			{
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
			else
				break;
		}
		lstadd_back(list,new_template((void*)new_list(text,derections)));
		token = GetNextToken(lexer);
		i++;
	}
	free(token);
	return(*list);
}

void minishell(char* all,t_global *g_global)
{
	
	t_lexer *lexer;
	t_template *list;
	t_template *error;


	list = NULL;
	lexer = init_lexer(all);
	list = Makelist(lexer,&list,g_global);
	error = list;
	if(error)
		lstiter(list,RMlist);
	if(list)
		lstiter(list,pMlist);
	free(lexer);
}