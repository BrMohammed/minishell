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
    t_text *text;
    t_derections *derections;
}t_Mlist;

typedef struct s_template
{
    void *content;
    struct s_template *next;
    struct s_template *prev;
}t_template;

t_token* init_token(char* value,int type);
t_lexer* init_lexer(char* src);
t_token *GetNextToken(t_lexer *lexer);
t_Mlist* new_list();
t_derections *new_derections();
t_text *new_text();
void Makelist(char* all);
void	*lstlast(void *lst);
void	lstadd_back(void **lst, void *new);
#endif
