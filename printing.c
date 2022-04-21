# include "minishell.h"
# include "libft/libft.h"

/***** ERROR *****/
void Perror(char* error)
{
    printf("minishael :syntax error near unexpected token '%s'\n",error);
}
int RText(t_template *lst,t_template *Mlst)
{
    while (lst)
	{
        if((((t_text*)lst->content)->data[0] == '|' && ((t_text*)lst->content)->order == 1) || (Mlst->next == NULL && ((t_text*)lst->content)->data[0] == '|'))
        {
            Perror("|");
            return(1);
        }
		lst = lst->next;
	}
    return(0);
}

int RDerections(t_template* lst)
{
    while (lst)
	{
         if(ft_strncmp(((t_derections*)lst->content)->file,"", 1) == 0 || ft_strncmp(((t_derections*)lst->content)->file,"|", 1) == 0)
         {
            Perror(">");
            return(1);
         }
            
		lst = lst->next;
	}
    return(0);
}

int RMlist(t_template* lst)
{
    int r;

    r = 0;
    while(lst)
    {
        if (r == 1)
            return(1);
        if(((t_Mlist *)lst->content)->text)
	        r = RText(((t_Mlist *)lst->content)->text,lst);
        if(((t_Mlist *)lst->content)->derections)
	       r =  RDerections(((t_Mlist *)lst->content)->derections);
        lst = lst->next;
    }
    return(0);
}

/***** PRINTING *****/
void pText(t_template* lst)
{
    while (lst)
	{
        printf("{%s -> %d -> %d}",((t_text*)lst->content)->data, ((t_text*)lst->content)->type,((t_text*)lst->content)->order);
		lst = lst->next;
	}
}

void pDerections(t_template* lst)
{
    while (lst)
	{
         if(((t_derections*)lst->content)->file && ((t_derections*)lst->content)->type)
	        printf(" |%s, %d , %d|",((t_derections*)lst->content)->file,((t_derections*)lst->content)->type,((t_derections*)lst->content)->order);
		lst = lst->next;
	}
}

void pMlist(t_template* lst)
{
    while(lst)
    {
        if(((t_Mlist *)lst->content)->text)
	        pText(((t_Mlist *)lst->content)->text);
        if(((t_Mlist *)lst->content)->derections)
	        pDerections(((t_Mlist *)lst->content)->derections);
        lst = lst->next;
    }
    printf("\n");
}


