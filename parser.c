# include "minishell.h"
# include "libft/libft.h"

// void text_list()
// {}

t_Mlist *rec_of_list(t_lexer *lexer, t_Mlist **list,t_text *text,t_derections *derections)
{
	t_token *token;
	t_Mlist *temp_list;
	t_derections *temp_derections;
	t_text *temp_text;


	temp_derections = NULL;
	temp_list = NULL;
	temp_text = NULL;
	token = GetNextToken(lexer); //<<<<< token have avery time type and value
	if(token->type == TYPE_EOF)
		return(0);
	while( token->type == TYPE_EOF)
	{
		text = NULL;
		derections = NULL;
		while (token->type == TYPE_TEXT)
		{
			temp_text = new_text(token->type);
			lstadd_back((void**)&text, (void*)temp_text);
			token = GetNextToken(lexer);
		}
		while(token->type != TYPE_TEXT && token->type != TYPE_PIPE && token->type == TYPE_EOF)
		{
			temp_derections = new_derections(token->type,GetNextToken(lexer)->value);
			lstadd_back((void**)&derections,(void*)temp_derections);
			token = GetNextToken(lexer);
		}
		if(token->type == TYPE_PIPE)
		{
			temp_list = new_list(text,derections);
			lstadd_back((void**)&list,(void*)temp_list);
		}
		else
		{
			new_list(text,derections);
		}
	}
	free(token);
	return(*list);
}

void Makelist(char* all)
{
	
	t_lexer *lexer;
	t_Mlist *list;
	t_text *text;
	t_derections *derections;

	text = NULL;
	derections = NULL;
	lexer = init_lexer(all);
	list = rec_of_list(lexer,&list,text,derections);
	free(lexer);
}