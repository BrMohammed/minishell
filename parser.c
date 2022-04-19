# include "minishell.h"
# include "libft/libft.h"

void Makelist(char* all)
{
	
	t_lexer *lexer;
	t_token *token;
	t_Mlist *list;
	t_text *text;
	t_derections derections;
	lexer = init_lexer(all);
	while(lexer->i <= lexer->size)
	{
		token = GetNextToken(lexer); //<<<<< token have avery time type and value
		
		if(token->type == TYPE_TEXT)
		{
			
		}
		else if(token->type != TYPE_TEXT && token->type != TYPE_PIPE)
		{

		}



		
		//for printing
		if(token->value != NULL)
			printf("%s    %d\n", token->value,token->type);
		free(token);
	}
	free(lexer);
}