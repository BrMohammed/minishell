# include "minishell.h"
# include "libft/libft.h"

t_token* init_token(char* value,int type)
{
    t_token *token;

    token = NULL;
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
    lexer->size = ft_strlen(src);
    lexer->i = 0;
    lexer->c = src[lexer->i];
    return (lexer);
}

t_Mlist* init_list(t_token* token)
{
    t_Mlist* list;

    list = malloc(sizeof(t_Mlist));
    list->data = token->value;
    list->type = token->type;
    list->next = NULL;
    list->prev = NULL;
}


