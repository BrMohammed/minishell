# include "lexer.h"
# include "libft/libft.h"

t_token* init_token(char* value,int type)
{
    t_token *token;
    token = malloc(sizeof(t_token));
    token->value = value;
    token->type = type;
    return(token);
}

t_lexer* init_lexer(char* src)
{
    t_lexer* lexer;

    lexer = malloc(sizeof(t_lexer));
    lexer->src = src;
    lexer->i = 0;
    lexer->c = src[lexer->i];
    return (lexer);
}