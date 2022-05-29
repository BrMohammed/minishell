# include "minishell.h"

void ExpandData(char* e,t_template **expand,int branch,t_template **text)
{
    int i;
    t_template *temp00;

    i = 0;
    temp00 = NULL;
    if(e[0] != '\0')
    {
        temp00 = *expand;
        if (temp00)
        {
            while (temp00->next != NULL)
                temp00 = temp00->next;
        }
        ((t_ExpandData*)temp00->content)->expan_data = ft_strdup(e);
    }
    if(branch == TEXT)
        ((t_text*)(*text)->content)->expand = *expand;
    else if(branch == DERECYION)
        ((t_derections*)(*text)->content)->expand = *expand;
}

char* CheckDolar(char *temp,char *key_ex)
{
    char *for_expand;
    int t;
    char* key;

    for_expand = malloc(2);
    for_expand[0] = '\0';
    for_expand[1] = '\0';
    t = ft_strlen(key_ex) + 1;
    key = ft_strdup("");
    while(temp[t] != '\0')
    {
        for_expand[0] = temp[t];
        key = ft_strjoin(key,for_expand);
        t++;
    }
    return(key);
}

void DolarWhoutQuat(char *key,char** e,t_template **expand,char *key_ex)
{
    int t;
    t_template *temp00;
    char *for_expand;

    temp00 = NULL;
    for_expand = malloc(2);
    for_expand[0] = '\0';
    for_expand[1] = '\0';
    t = 0;
    while(key[t] != '\0' )
    {
        for_expand[0] = key[t];
        *e = ft_strjoin(*e,for_expand);
        t++;
        if(key[t] == 32)
        {
            temp00 = *expand;
            if (temp00)
            {
                while (temp00->next != NULL)
                    temp00 = temp00->next;
            }
            ((t_ExpandData*)temp00->content)->expan_data = ft_strdup(*e);
            ((t_ExpandData*)temp00->content)->key = key_ex;
            free(*e);
            *e = ft_strdup(""); 
            lstadd_back(expand, new_template(new_expand(*e,key_ex)));
            while(key[t] == 32)
                t++;
        }
    }
}

void quat_skip(char *quat,char data,char **e)
{
    char* temp;

    temp = malloc(2);
    temp[0] = '\0';
    temp[1] = '\0';
    if((*quat == '\'' && data == '\'') || (*quat == '"' && data == '"'))
        *quat = '\0';
    else if(data == '\'' && *quat != '"')
        *quat = '\'';
    else if(data == '"' && *quat != '\'')
        *quat = '"';
    else
    {
        temp[0] = data; 
        *e = ft_strjoin(*e,temp);
    }
    free(temp);
}

char* MakeTheKey(char *data, int *j,char** key_ex)
{
    char* key;
    int i;
    char* temp;

    key = ft_strdup("");
    temp = ft_strdup("");
    while(data[*j] && data[*j] != '$' && ((data[*j] >= 'a' && data[*j] <= 'z') || (data[*j] >= 'A' && data[*j] <= 'Z') /*continue join when dejet or alpha or - */
        || (data[*j] >= '0' && data[*j] <= '9') || (data[*j] == '-') || data[*j] == 32))
    {
        temp[0] = data[*j];
        key = ft_strjoin(key,temp);
        *j = *j + 1;
    }
   *j = *j - 1; /* if char is dolar*/
    *key_ex = strdup(key);
    key = ft_strjoin(key,"=");
    free(temp);
    temp = NULL;
    i = 0;
    while (g_global.envp[i] && temp == NULL) /*serch in env */
    {
        temp = ft_strnstr(g_global.envp[i], key,ft_strlen(key));
        i++;
    }
    free(key);
    return(temp);
}

char* Begin_Dolar(int *j,char* data,char **e,char **key_ex)
{
    char* temp;

    *key_ex = NULL;
    temp = ft_strdup("");
    temp = MakeTheKey(data,j,key_ex); /*key of dolar*/
    if(temp == NULL) /* key is null*/
    {
        *e = ft_strjoin(*e,"");
        temp = NULL;
    }
    return(temp);
}

int Dolar(char *data,char **e,char quat,t_template **expand)
{
    int j;
    int i;
    char* temp;
    char* key_ex;
    char* key;

    i = g_global.g_ii;
    i++;
    j = i;
    temp = Begin_Dolar(&j,data,e,&key_ex);
    if(temp != NULL)
    {
        key = CheckDolar(temp,key_ex);
        temp = ft_strdup("");
        if(quat != '"')
            DolarWhoutQuat(key,e,expand,key_ex);
        else
        {
            *e = ft_strjoin(*e,key);
            ((t_ExpandData*)(*expand)->content)->key = key_ex;
        }
            
        temp = NULL;
        free(key);
    }
    i = j;
    return(i);
}

void MaleKeyOfDlar(char *data,t_template **text,int branch)
{
    int i;
    char *e;
    char* temp;
    char quat;
    t_template *expand;

    i = 0;
    e = ft_strdup("");
    expand = NULL;
    lstadd_back(&expand, new_template(new_expand("","")));
    while(i <= (int)ft_strlen(data))
    {
        temp = ft_strdup("");
        g_global.g_ii = i;
        if(data[i] != '$')
            quat_skip(&quat,data[i],&e); /* quat set*/
        else if(data[i] == '$' && quat == '\'') /*when singelquet and dolar exest sqiping the key*/
        {
            temp[0] = data[i]; 
            e = ft_strjoin(e,temp);
        }
        else if(data[i] == '$')/*dolar in text or inter of doublequet*/
            i = Dolar(data,&e,quat,&expand);
        free(temp);
        i++;
    }
    ExpandData(e,&expand,branch,text);
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
        if((((t_text*)lst->content)->data[0] == '|' && ((t_text*)lst->content)->order == 1))
        {
            Perror("|");
            return(1);
        }
        if(((t_text*)lst->content)->type == TYPE_ERROR)
        {
            printf("Syntax Error\n");
            return(1);
        }
        if((((t_text*)lst->content)->data[0] == '|' && lst->next == NULL))
            return(2);
        MaleKeyOfDlar(((t_text*)lst->content)->data,&lst,TEXT);
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
        MaleKeyOfDlar(((t_derections*)lst->content)->file,&lst,DERECYION);
        if(((t_derections*)lst->content)->type == TYPE_Rredirection)
            ((t_derections*)lst->content)->fd = open(((t_derections*)lst->content)->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);  //out >
        if(((t_derections*)lst->content)->type == TYPE_DRredirection)
            ((t_derections*)lst->content)->fd = open(((t_derections*)lst->content)->file, O_WRONLY | O_CREAT | O_APPEND, 0644);  //out >>
         if(((t_derections*)lst->content)->type == TYPE_Lredirection)
        {
            ((t_derections*)lst->content)->fd = open(((t_derections*)lst->content)->file, O_RDONLY);
            if(((t_derections*)lst->content)->fd == -1)
            {
                printf("minishell: %s: No such file or directory\n",((t_derections*)lst->content)->file);
            }
        }
		lst = lst->next;
	}
    return(3);
}

int RMlist(t_template* lst)
{
    int r;
    int r2;

    while(lst)
    { 
        r = 0;
        r2 = 0;
        if(((t_Mlist *)lst->content)->text)
	        r = RText(((t_Mlist *)lst->content)->text,lst);
        if(((t_Mlist *)lst->content)->derections)
	       r2 =  RDerections(((t_Mlist *)lst->content)->derections);
        if(r == 2 & r2 == 0)
        {
            Perror("|");
            return(1);
        }
        lst = lst->next;
        if (r == 1 || r2 == 1)
            return(1);
    }
    return(0);
}


/***** PRINTING *****/
char** pText(t_template* lst)
{
    t_template *exp;
    int number_of_cases;
    char **c;

    c = creat_table(lst);
    number_of_cases = 0;
    while (lst)
	{
        exp = ((t_text*)lst->content)->expand;
        if(((t_text*)lst->content)->data != NULL)
        {
            //printf("{%s -> type : %d -> ord : %d} (>>) ",((t_text*)lst->content)->data, ((t_text*)lst->content)->type,((t_text*)lst->content)->order);
        }
            
         while(exp) /*   >>>>>   for looping in the expanded link of node text*/
        { 
            //printf("{%s ==>> %s}",((t_ExpandData*)exp->content)->expan_data,((t_ExpandData*)exp->content)->key);
            if(ft_strncmp(((t_ExpandData*)exp->content)->expan_data, "|",1) != 0)
            {
                c[number_of_cases] = ft_strdup(((t_ExpandData*)exp->content)->expan_data);
                number_of_cases++;
            }
            exp = exp->next;
        }
		lst = lst->next;

	}
    return(c);
}

char **pDerections(t_template* lst)
{
    t_template *exp;

    while (lst)
	{
        exp = ((t_derections*)lst->content)->expand;
         if(((t_derections*)lst->content)->file != NULL && ((t_derections*)lst->content)->type)
         {
            //printf(" |%s, type : %d , ord : %d , fd : %d| (>>) ",((t_derections*)lst->content)->file,((t_derections*)lst->content)->type,((t_derections*)lst->content)->order,((t_derections*)lst->content)->fd);
         }
	        
         while(exp) /*   >>>>>   for looping in the expanded link of node text*/
        { 
            //printf("{%s ==>> %s}",((t_ExpandData*)exp->content)->expan_data,((t_ExpandData*)exp->content)->key);
            exp = exp->next;
        }
		lst = lst->next;
	}
    return(0);
}


void pMlist(t_template* lst)
{
    char	**c;
    char	*path;
    int index;
    int t;
    int lastFd = -1;
    t_template *tmp = lst;

    index = 0;
    c = NULL;
    while(lst)
    {
        path = NULL; 
        // if(((t_Mlist *)lst->content)->derections)
        // {
        //     pDerections(((t_Mlist *)lst->content)->derections);
        // }
        /**********   pipe  *********/
        if(((t_Mlist *)lst->content)->text)
        {
            c = pText(((t_Mlist *)lst->content)->text);
            if(c != NULL)
            {
                 path_finder(&path, c, g_global.envp);
                 lastFd = pipeline(lst,path,lastFd,c);
                if (path != NULL)
                    free(path);
                t = 0;
                while (c[t])
                    free(c[t++]);
            }
        }
        free(c);
       /*******************/

        index++;
        lst = lst->next;
    }
    int ex;
    int lastone;
    while(tmp->next != NULL)
    {
        waitpid(((t_Mlist *)tmp->content)->pid, &ex, 0);
        tmp = tmp->next;
    }
    waitpid(((t_Mlist *)tmp->content)->pid, &lastone, 0);
    // echo $?
    
    // while(index > 0)
    // { 
    //     wait(NULL);
    //     index--;
    // }
}
