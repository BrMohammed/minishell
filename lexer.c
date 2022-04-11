#include "lexer.h"
# include "libft/libft.h"

void GetNextToken(t_lexer *lexer)
{
    t_token *token;
    char* temp_char;

    temp_char = malloc(2);
    temp_char[0] = lexer->c;
    temp_char[1]='\0';
    lexer->i++;
    token = init_token(temp_char,TYPE_TEXT);
    printf("=>%d\n",lexer->i);
    printf("token [%s]  , %d \n",token->value,token->type);
}

void PrintTokens(char* all)
{
    
    t_lexer *lexer;
    t_token *token;
    
    lexer = init_lexer(all);
    GetNextToken(lexer);
    GetNextToken(lexer);
}
int main(int argc, char** argv, char** envp)
{
    char    *all;

    if(argc == 1)
    {
        while (1)
        {
            all = readline("minishell ");
            PrintTokens(all);
            free(all);
        }
    }
    return (0);
}