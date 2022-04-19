# ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
#include <readline/readline.h>

typedef struct s_token
{
    char* value;
    enum
    { 
        TYPE_TEXT ,
        TYPE_DLredirection,
        TYPE_DRredirection,
        TYPE_Lredirection,
        TYPE_Rredirection,
        TYPE_PIPE,
        TYPE_EOF,
        TYPE_ERROR,
    }type;
}t_token;

typedef struct s_lexer
{
    char* src;
    unsigned int size;
    unsigned int i;
    char c;

}t_lexer;

typedef struct s_text
{
    char *data;
    int order;
}t_text;

typedef struct s_derections
{
    char *file;
    int order;
    int type;
}t_derections;

typedef struct s_Mlist
{
    void *text;
    void *derections;
}t_Mlist;

typedef struct s_template
{
    void    *content;
    struct  s_template *next;
    struct  s_template *prev;
}t_template;

t_token* init_token(char* value,int type);
t_lexer* init_lexer(char* src);
t_token *GetNextToken(t_lexer *lexer);

t_template	*new_template(void *content);
void	lstadd_back(t_template **lst, t_template *new);
t_template	*lstlast(t_template *lst);

t_Mlist* new_list( t_template* text,t_template* derections);
t_derections *new_derections(char *file,int type);
t_text *new_text(char *data);

void Makelist(char* all);
#endif
