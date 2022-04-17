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

t_childe* init_childe(t_token* token)
{
    t_childe* childe;
    childe = malloc(sizeof(t_childe));
    childe->token = token;
    return(childe);
}

t_tree* tree(t_childe* childe)
{
    t_tree  *tree;
    
    tree = malloc(sizeof(t_tree));
    tree->childe = childe;
    tree->Left = NULL;
    tree->Right = NULL;
    tree->prev = NULL;
    return (tree);
}