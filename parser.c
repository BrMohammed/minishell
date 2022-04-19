# include "minishell.h"
# include "libft/libft.h"


t_template *rec_of_list(t_lexer *lexer, t_template **list,t_template *text,t_template *derections)
{
	t_token *token;

	token = GetNextToken(lexer); //<<<<< token have avery time type and value
	if(token->type == TYPE_EOF)
		return(0);
	text = NULL;
	derections = NULL;
	while (token->type == TYPE_TEXT && token->type != TYPE_EOF )
	{
		lstadd_back(&text, new_template((void*)new_text(token->value)));
		token = GetNextToken(lexer);
	}
	while(token->type != TYPE_TEXT && token->type != TYPE_PIPE && token->type != TYPE_EOF)
	{
		lstadd_back(&derections,new_template((void*)new_derections(GetNextToken(lexer)->value,token->type)));
		token = GetNextToken(lexer);
	}
	lstadd_back(list,new_template((void*)new_list(text,derections)));
	while(token->type == TYPE_PIPE)
	{
		text = NULL;
		derections = NULL;
		while (token->type == TYPE_TEXT && token->type != TYPE_EOF )
		{
			lstadd_back(&text, new_template((void*)new_text(token->value)));
			token = GetNextToken(lexer);
		}
		while(token->type != TYPE_TEXT && token->type != TYPE_PIPE && token->type != TYPE_EOF)
		{
			lstadd_back(&derections,new_template((void*)new_derections(GetNextToken(lexer)->value,token->type)));
			token = GetNextToken(lexer);
		}
		lstadd_back(list,new_template((void*)new_list(text,derections)));
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
	printf("%s\n",((t_text *)((t_Mlist *)list->content)->text->content)->data);
	free(lexer);
}

// pMlist(void* content)
// {
// 	iter(text,pText)
// 	iter(redor, predir)
// }



// pText(void* content)
// {
// 	while (args)
// 	{
// 		/* code */
// 	}
	
// }


// pRedit(void* content)
// {
// 	if (asf>> ><<<)
// 	asdas
// }