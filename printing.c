# include "minishell.h"
# include "libft/libft.h"

/***** ERROR *****/
void Perror(char* error)
{
    printf("minishael :syntax error near unexpected token '%s'\n",error);
}
int RText(t_template *lst,t_template *Mlst)
{
    (void)Mlst;
    while (lst)
	{
        if((((t_text*)lst->content)->data[0] == '|' && ((t_text*)lst->content)->order == 1) || (((t_text*)lst->content)->data[0] == '|' && lst->next == NULL))
        {
            Perror("|");
            return(1);
        }
        if(((t_text*)lst->content)->type == TYPE_ERROR)
        {
            printf("Syntax Error\n");
            return(1);
        }

		lst = lst->next;
	}
    return(0);
}

int RDerections(t_template* lst)
{
    char* t_temp;


    
    while (lst)
	{
        if(((t_derections*)lst->content)->type == TYPE_Lredirection)
            t_temp = "<";
        if(((t_derections*)lst->content)->type == TYPE_Rredirection)
            t_temp = ">";
        if(((t_derections*)lst->content)->type == TYPE_DLredirection)
            t_temp = "<<";
        if(((t_derections*)lst->content)->type == TYPE_DRredirection)
            t_temp = ">>";
        if(ft_strncmp(((t_derections*)lst->content)->file,"", 1) == 0 || ft_strncmp(((t_derections*)lst->content)->file,"|", 1) == 0)
        {
            Perror(t_temp);
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
        if(((t_Mlist *)lst->content)->text)
	        r = RText(((t_Mlist *)lst->content)->text,lst);
        if(((t_Mlist *)lst->content)->derections)
	       r =  RDerections(((t_Mlist *)lst->content)->derections);
        lst = lst->next;
        if (r == 1)
            return(1);
    }
    return(0);
}

/***** PRINTING *****/
void pText(t_template* lst)
{
    int i = 0;
    int j = 0;
    char **env = NULL;
    char	*en;
    char *e;

    e = ft_strdup("");
    while (lst)
	{
        if(((t_text*)lst->content)->data[0] == '$' && ((t_text*)lst->content)->data[1] != '\0')
        {
            env = ft_split(((t_text*)lst->content)->data,'$');
            while(env[j])
            {
                env[j] = ft_strjoin(env[j],"=");
                j++;
            }
            j = 0;
            while (env[j])
            {
                while(g_global.envp[i] && en == NULL)
                {
                    en = ft_strnstr(g_global.envp[i], env[j],ft_strlen(env[j]));///>>>>addd strstr
                    if(en != NULL)
                    {
                        e = ft_strjoin(e,en);
                        en = NULL;
                        i = 0;
                        break;
                    }
                    i++;
                }
                j++;
            }
		    if(e)
            {
                ((t_text*)lst->content)->data = ft_strdup(e);
            }
        }
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
        printf("\n");
    }
}


