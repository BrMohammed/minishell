# ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
#include <readline/readline.h>

#define TEXT  1
#define DERECYION 0


typedef struct s_global
{
    char **envp;
    int g_i;
}t_global;

t_global g_global;

typedef struct s_template
{
    void    *content;
    struct  s_template *next;
    struct  s_template *prev;
}t_template;

typedef struct s_token
{
    char* value;
    enum
    { 
        TYPE_TEXT ,
        TYPE_QUOTE,
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

typedef struct s_ExpandData
{
    char** expan_data;
    char* key;
}t_ExpandData;

typedef struct s_text
{
    char *data;
    t_template *expand;
    int order;
    int type;
}t_text;

typedef struct s_derections
{
    char *file;
    t_template *expand;
    int order;
    int type;
}t_derections;

typedef struct s_Mlist
{
    t_template *text;
    t_template *derections;
    int order;
}t_Mlist;



t_token* init_token(char* value,int type);
t_lexer* init_lexer(char* src);
t_token *GetNextToken(t_lexer *lexer);

t_template	*new_template(void *content);
void	lstadd_back(t_template **lst, t_template *new);
t_template	*lstlast(t_template *lst);
void	lstiter(t_template *lst, void (*f)(void *));

t_Mlist* new_list( t_template* text,t_template* derections, int order);
t_derections *new_derections(char *file,int type,int order);
t_text *new_text(char *data,int type,int order);
t_ExpandData *new_expand(char** expand_data, char*key);

void *minishell(char* all);
void pMlist(t_template* lst);
int RMlist(t_template* lst);
#endif
