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

t_Mlist* new_list( t_text* text,t_derections* derections)
{
    t_Mlist* list;
   
    list = malloc(sizeof(t_Mlist));
    list->text = text;
    list->derections = derections;
    list->next = NULL;
    list->prev = NULL;
    return(list);
}

t_derections *new_derections(char *file,int type)
{
    t_derections *derections;

    derections = malloc(sizeof(t_derections));
    derections->file = file;
    derections->type = type;
    derections->order = 0;
    derections->next = NULL;
    derections->prev = NULL;
    return(derections);
}

t_text *new_text(char *data)
{
    t_text *text;

    text = malloc(sizeof(t_text));
    text->data = data;
    text->order = 0;
    text->next = NULL;
    text->prev = NULL;
    return(text);
}


