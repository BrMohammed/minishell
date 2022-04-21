# include "minishell.h"
# include "libft/libft.h"

/***** ERROR *****/
void Perror()
{
    printf("ERROR\n");
    exit(0);
}
void RText(t_template *lst,t_template *Mlst)
{
    (void)Mlst;
    while (lst)
	{
        if(((t_text*)lst->content)->data[0] == '|' && ((t_text*)lst->content)->order == 1)
            Perror();
        
        if(Mlst->next == NULL && ((t_text*)lst->content)->data[0] == '|' )
            Perror();
		lst = lst->next;
	}
}

void RDerections(t_template* lst)
{
    while (lst)
	{
         if(ft_strncmp(((t_derections*)lst->content)->file,"", 1) == 0 || ft_strncmp(((t_derections*)lst->content)->file,"|", 1) == 0)
            Perror();
		lst = lst->next;
	}
}

void RMlist(t_template* lst)
{
    while(lst)
    {
        if(((t_Mlist *)lst->content)->text)
	        RText(((t_Mlist *)lst->content)->text,lst);
        if(((t_Mlist *)lst->content)->derections)
	        RDerections(((t_Mlist *)lst->content)->derections);
        lst = lst->next;
    }
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


