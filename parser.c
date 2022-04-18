# include "minishell.h"
# include "libft/libft.h"

void MakeTree(char* all)
{
	
	t_lexer *lexer;
	t_token *token;
	lexer = init_lexer(all);
	while(lexer->i <= lexer->size)
	{
		token = GetNextToken(lexer); //<<<<< token have avery time type and value

		

		//for printing
		if(token->value != NULL)
			printf("%s    %d\n", token->value,token->type);
		free(token);
	}
	free(lexer);
}