# include "minishell.h"
# include "libft/libft.h"

void rec_of_list(t_lexer *lexer)
{
	t_token *token;

	token = GetNextToken(lexer); //<<<<< token have avery time type and value
	if(token->type == TYPE_EOF)
		return(0);
	if(token->type == TYPE_TEXT)
	{
		
	}
	else if(token->type != TYPE_TEXT && token->type != TYPE_PIPE)
	{

	}
	else if(token->type == TYPE_PIPE)
	{
		
	}
	free(token);
	rec_of_list(lexer);
}

void Makelist(char* all)
{
	
	t_lexer *lexer;
	t_Mlist *list;
	t_text *text;
	t_derections derections;
	lexer = init_lexer(all);
	rec_of_list(lexer);
	free(lexer);
}