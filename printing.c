# include "minishell.h"
# include "libft/libft.h"


void MaleKeyOfDlar(char *data,t_template **text,int branch)
{
    int i = 0;
    int j = 0;
    int t = 0;
    char *e;
    char* temp;
    char* key;
    char quat;
    char *for_expand;
    t_template *expand;
    char* key_ex;
    t_template *temp00 = NULL;

    i = 0;
    j = 0;
    e = ft_strdup("");
    expand = NULL;
    temp = NULL;
    key_ex = NULL;
    lstadd_back(&expand, new_template(new_expand(e,key_ex)));
    while(i <= (int)ft_strlen(data))
    {
        temp = malloc(2);
        temp[0] = '\0';
        temp[1] = '\0';
        for_expand = malloc(2);
        for_expand[0] = '\0';
        for_expand[1] = '\0';
        if(data[i] != '$')
        {
            /* quat set*/
            if((quat == '\'' && data[i] == '\'') || (quat == '"' && data[i] == '"'))
            {
                quat = '\0';
                printf("%c---> hire\n",quat);
            }
            else if(data[i] == '\'' && quat != '"')
            { 
                quat = '\'';
                printf("%c--->\n",quat);
            }
            else if(data[i] == '"' && quat != '\'')
            {
                quat = '"';
                printf("%c--->\n",quat);
            }
            else
            {
                temp[0] = data[i]; 
                e = ft_strjoin(e,temp);
            }
        }
        else if(data[i] == '$' && quat == '\'') /*when singelquet and dolar exest sqiping the key*/
        {
            temp[0] = data[i]; 
            e = ft_strjoin(e,temp);
        }
        else if(data[i] == '$')/*dolar in text or inter of doublequet*/
        {
            key = ft_strdup("");
            i++;
            j = i;
            while(data[j] && data[j] != '$' && ((data[j] >= 'a' && data[j] <= 'z') || (data[j] >= 'A' && data[j] <= 'Z') /*continue join when dejet or alpha or - */
		        || (data[j] >= '0' && data[j] <= '9') || (data[j] == '-') || data[j] == 32))
            {
                temp[0] = data[j];
                key = ft_strjoin(key,temp);
                j++;
            }
            j--; /* if char is dolar*/
            key_ex = strdup(key);
            key = ft_strjoin(key,"=");
            t = ft_strlen(key);
            free(temp);
            temp = NULL;
            i = 0;
            while (g_global.envp[i] && temp == NULL) /*serch in env */
            {
                temp = ft_strnstr(g_global.envp[i], key,ft_strlen(key));
                i++;
            }
            free(key);
            key = ft_strdup("");
            if(temp == NULL) /* key is null*/
            {
                e = ft_strdup("");
                temp = NULL;
                i = j;
                free(key);
                continue;
            }
            while(temp[t] != '\0')
            {
                for_expand[0] = temp[t];
                key = ft_strjoin(key,for_expand);
                t++;
            }
            temp = ft_strdup("");
            if(quat != '"')
            {
                t = 0;
                while(key[t] != '\0' )
                {
                    for_expand[0] = key[t];
                    e = ft_strjoin(e,for_expand);
                    t++;
                    if(key[t] == 32)
                    {
                        temp00 = expand;
                        if (temp00)
                        {
                            while (temp00->next != NULL)
                                temp00 = temp00->next;
                        }
                        ((t_ExpandData*)temp00->content)->expan_data = ft_strdup(e);
                        ((t_ExpandData*)temp00->content)->key = key_ex;
                        free(e);
                        e = ft_strdup(""); 
                        lstadd_back(&expand, new_template(new_expand(e,key_ex)));
                        while(key[t] == 32)
                            t++;
                    }
                }
            }
            else
                e = ft_strjoin(e,key);
            temp = NULL;
            i = j;
            free(key);
        }
        free(temp);
        free(for_expand);
        i++;
    }
    if(e[0] != '\0')
    {
        i = 0;
        temp00 = expand;
        if (temp00)
        {
            while (temp00->next != NULL)
                temp00 = temp00->next;
        }
        ((t_ExpandData*)temp00->content)->expan_data = ft_strdup(e);
    }
    if(branch == TEXT)
        ((t_text*)(*text)->content)->expand = expand;
    else if(branch == DERECYION)
        ((t_derections*)(*text)->content)->expand = expand;
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
        MaleKeyOfDlar(((t_text*)lst->content)->data,&lst,TEXT);
		lst = lst->next;
	}
    return(0);
}

int RDerections(t_template* lst)
{
    char* t_temp;
    char *data;
    
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
        MaleKeyOfDlar(((t_derections*)lst->content)->file,&lst,DERECYION);
          if(((t_derections*)lst->content)->type == TYPE_Rredirection || ((t_derections*)lst->content)->type == TYPE_DRredirection)
          {
            ((t_derections*)lst->content)->fd = open(data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            close(((t_derections*)lst->content)->fd);
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
    t_template *exp;
    while (lst)
	{
        exp = ((t_text*)lst->content)->expand;
        if(((t_text*)lst->content)->data != NULL)
            printf("{%s -> %d -> %d}",((t_text*)lst->content)->data, ((t_text*)lst->content)->type,((t_text*)lst->content)->order);
         while(exp) /*   >>>>>   for looping in the expanded link of node text*/
        { 
            printf("{%s ==>> %s}",((t_ExpandData*)exp->content)->expan_data,((t_ExpandData*)exp->content)->key);
            exp = exp->next;
        }
		lst = lst->next;
	}
}

void pDerections(t_template* lst)
{
    t_template *exp;
    while (lst)
	{
        exp = ((t_derections*)lst->content)->expand;
         if(((t_derections*)lst->content)->file != NULL && ((t_derections*)lst->content)->type)
	        printf(" |%s, type : %d , ord : %d , fd : %d|",((t_derections*)lst->content)->file,((t_derections*)lst->content)->type,((t_derections*)lst->content)->order,((t_derections*)lst->content)->fd);
         while(exp) /*   >>>>>   for looping in the expanded link of node text*/
        { 
            printf("{%s ==>> %s}",((t_ExpandData*)exp->content)->expan_data,((t_ExpandData*)exp->content)->key);
            exp = exp->next;
        }
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
