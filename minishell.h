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
    char **data;
    int order;
    struct s_text *next;
    struct s_text *prev;
}t_text;

typedef struct s_derections
{
    char **derections;
    int order;
     enum
    { 
        TYPE_DLredirection,
        TYPE_DRredirection,
        TYPE_Lredirection,
        TYPE_Rredirection,
    }type;
    struct s_derections *next;
    struct s_derections *prev;
}t_derections;

typedef struct s_Mlist
{
    t_text *text;
    t_derections *derections;
    struct s_Mlist *next;
    struct s_Mlist *prev;
}t_Mlist;

t_token* init_token(char* value,int type);
t_lexer* init_lexer(char* src);
t_token *GetNextToken(t_lexer *lexer);
t_Mlist* init_list();
t_derections *init_derections();
t_text *init_text();
void MakelistMM(char* all);
#endif