# include "minishell.h"

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

t_Mlist* new_list( t_template* text,t_template* derections, int order)
{
    t_Mlist* list;
   
    list = malloc(sizeof(t_Mlist));
    list->text = text;
    list->derections = derections;
    list->order =  order;
    return(list);
}

t_derections *new_derections(char *file,int type,int i)
{
    t_derections *derections;

    derections = malloc(sizeof(t_derections));
    derections->file = ft_strdup(file);
    derections->expand = NULL;
    derections->type = type;
    derections->order = i;
    derections->fd = 1;
    return(derections);
}

t_text *new_text(char *data,int type,int i)
{
    t_text *text;

    text = malloc(sizeof(t_text));
    text->data = ft_strdup(data);
    text->type = type;
    text->expand = NULL;
    text->order = i;
    return(text);
}