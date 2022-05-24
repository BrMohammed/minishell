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

printf("%p==\n",src);
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


t_ExpandData *new_expand(char* expand_data, char*key)
{
    t_ExpandData *expand;

    expand = malloc(sizeof(t_ExpandData));
    expand->expan_data = expand_data;
    expand->key = key;
    return(expand);
}

void	lstadd_back(t_template **lst, t_template *new)
{
	t_template	*temp;

	if (*lst)
	{	
		temp = lstlast(*lst);
        new->prev = temp;
		temp->next = new;
	}
	else
		*lst = new;
}

t_template	*lstlast(t_template *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

t_template	*new_template(void *content)
{
	t_template	*index;

	index = (t_template *)malloc(sizeof(t_template));
	if (!index)
		return (NULL);
	index->content = content;
	index->next = NULL;
    index->prev = NULL;
	return (index);
}

void	lstiter(t_template *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
