# include "minishell.h"
# include "libft/libft.h"


t_template *rec_of_list(t_lexer *lexer, t_template **list,t_template *text,t_template *derections)
{
	t_token *token;
	int i = 0;

	token = GetNextToken(lexer); //<<<<< token have avery time type and value
	if(token->type == TYPE_EOF)
		return(0);
	// text = NULL;
	// derections = NULL;
	// while (token->type == TYPE_TEXT)
	// {
	// 	lstadd_back(&text, new_template((void*)new_text(token->value,token->type)));
	// 	token = GetNextToken(lexer);
	// }
	// while(token->type != TYPE_TEXT && token->type != TYPE_PIPE && token->type != TYPE_EOF)
	// {
	// 	lstadd_back(&derections,new_template((void*)new_derections(GetNextToken(lexer)->value,token->type)));
	// 	token = GetNextToken(lexer);
	// }
	// if (token->type == TYPE_PIPE)
	// 	{
	// 		lstadd_back(&text, new_template((void*)new_text(token->value,token->type)));
	// 		token = GetNextToken(lexer);
	// 	}
	// lstadd_back(list,new_template((void*)new_list(text,derections)));
	//printf("pipe :  %d\n" , i++);
	while(token->type != TYPE_EOF)
	{
		text = NULL;
		derections = NULL;
		
		while (token->type == TYPE_TEXT)
		{
			lstadd_back(&text, new_template((void*)new_text(token->value,token->type,i)));
			token = GetNextToken(lexer);
		}
		while(token->type != TYPE_TEXT && token->type != TYPE_PIPE && token->type != TYPE_EOF)
		{
			lstadd_back(&derections,new_template((void*)new_derections(GetNextToken(lexer)->value,token->type,i)));
			token = GetNextToken(lexer);
		}
		if (token->type == TYPE_PIPE)
		{
			lstadd_back(&text, new_template((void*)new_text(token->value,token->type,i)));
		}
			
		lstadd_back(list,new_template((void*)new_list(text,derections)));
		token = GetNextToken(lexer);
		i++;
	}
	free(token);
	return(*list);
}

void Makelist(char* all)
{
	
	t_lexer *lexer;
	t_template *list;
	t_template *text;
	t_template *derections;

	text = NULL;
	derections = NULL;
	list = NULL;
	lexer = init_lexer(all);
	list = rec_of_list(lexer,&list,text,derections);
	if(list)
		lstiter(list,pMlist);
	free(lexer);
}