# include "minishell.h"
# include "libft/libft.h"


char* MaleKeyOfDlar(char *data)
{
    int i = 0;
    int j = 0;
    char *e;
    char* temp;
    char* key;
    char quat;

    i = 0;
    j = 0;
    e = ft_strdup("");
    while(i <= (int)ft_strlen(data))
    {
        temp = malloc(2);
        temp[0] = '\0';
        temp[1] = '\0';
        if(data[i] != '$' && data[i])
        {
            if((quat == '\'' && data[i] == '\'') || (quat == '"' && data[i] == '"'))
                quat = '\0';
            else if(data[i] == '\'' && quat != '"')
                quat = '\'';
            else if(data[i] == '"' && quat != '\'')
                quat = '"';
            else
            {
                temp[0] = data[i]; 
                e = ft_strjoin(e,temp);
            }
        }
        else if(data[i] == '$' && quat == '\'')
        {
            temp[0] = data[i]; 
            e = ft_strjoin(e,temp);
        }
        if(data[i] == '$'  && quat != '\'')
        {
            key = ft_strdup("");
            i++;
            j = i;
            while(data[j] && data[j] != '$'  && ((data[j] >= 'a' && data[j] <= 'z') || (data[j] >= 'A' && data[j] <= 'Z')
		                || (data[j] >= '0' && data[j] <= '9') || data[j] == '-'))
            {
                temp[0] = data[j];
                key = ft_strjoin(key,temp);
                j++;
            }
            if(data[j] == '$')
                j--;
            key = ft_strjoin(key,"=");
            i = 0;
            free(temp);
            temp = NULL;
            while (g_global.envp[i] && temp == NULL)
            {
                temp = ft_strnstr(g_global.envp[i], key,ft_strlen(key));
                i++; 
            }
            e = ft_strjoin(e,temp);
            if(e == NULL)
                e = ft_strdup("");
            temp = NULL;
            i = j;
            free(key);
        }
        i++;
    }
    
	return(e);
}

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
    char *data;

    while (lst)
	{
        data = MaleKeyOfDlar(((t_text*)lst->content)->data);
        if(data == NULL)
            data = ft_strdup("");
        ((t_text*)lst->content)->data = ft_strdup(data);
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


