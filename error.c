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
    free(for_expand);
    return(key);
}

void DolarWhoutQuat(t_Dolar *var)//?
{
    int t;
    t_template *temp00;
    char *for_expand;

    temp00 = NULL;
    for_expand = malloc(2);
    for_expand[1] = '\0';
    t = 0;
    while(var->key[t] != '\0' )
    {
        for_expand[0] = var->key[t];
        var->e = ft_strjoin(var->e,for_expand);
        t++;
        if(var->key[t] == 32)
        {
            temp00 = var->expand;
            if (temp00)
            {
                while (temp00->next != NULL)
                    temp00 = temp00->next;
            }
            ((t_ExpandData*)temp00->content)->expan_data = ft_strdup(var->e);
            ((t_ExpandData*)temp00->content)->key = var->key_ex;
            free(var->e);
            var->e = ft_strdup(""); 
            lstadd_back(&var->expand, new_template(new_expand(var->e,var->key_ex)));
            while(var->key[t] == 32)
                t++;
        }
    }
    free(for_expand);
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

void if_dolar_in_env(char *data,t_Dolar *var)
{
    int  i;

    while(data[var->j] && data[var->j] != '$' && ((data[var->j] >= 'a' && data[var->j] <= 'z') || (data[var->j] >= 'A' && data[var->j] <= 'Z') /*continue join when dejet or alpha or - */
        || (data[var->j] >= '0' && data[var->j] <= '9') || (data[var->j] == '-') || data[var->j] == 32))
    {
        var->temp[0] = data[var->j];
        var->key = ft_strjoin(var->key,var->temp);
        var->j++;
    }
    var->j--; /* if char is dolar*/
    var->key_ex = strdup(var->key);
    var->key = ft_strjoin(var->key,"=");
    free(var->temp);
    var->temp = NULL;
    i = 0;
    while (g_global->envp[i] && var->temp == NULL) /*serch in env */
    {
        var->temp = ft_strnstr(g_global->envp[i], var->key,ft_strlen(var->key));
        i++;
    }
}

void MakeTheKey(char *data,t_Dolar *var)
{
    var->key = ft_strdup("");
    var->temp = ft_strdup("");
    if(data[var->j] == '?') // flage chek
    {
        free(var->temp);
        var->temp = NULL;
        var->temp = ft_itoa(g_global->g_flags);
    }
    else
        if_dolar_in_env(data,var);
    free(var->key);
}

void Begin_Dolar(char* data,t_Dolar *var)
{
    var->key_ex = NULL;
    MakeTheKey(data,var); /*key of dolar*/
    if(var->temp == NULL) /* key is null*/
    {
        var->e = ft_strjoin(var->e,"");
        var->temp = NULL;
    }
}

int chek_if_flag(char *temp)
{
    int i;

    i = 0;
    while(temp[i] != '\0')
    {
        if(temp[i] == '=')
            return(0);
        i++;
    }
    return(1);
}

void detect_dolar(t_Dolar *var)
{
    if(chek_if_flag(var->temp) == 0)
        var->key = CheckDolar(var->temp,var->key_ex); // begin key after =
    else
        var->key = var->temp;
    var->temp = ft_strdup("");
    if(var->quat != '"')
        DolarWhoutQuat(var);
    else
    {
        var->e = ft_strjoin(var->e,var->key);
        ((t_ExpandData*)(var->expand)->content)->key  = var->key_ex;
    }
}

int Dolar(char *data,t_Dolar *var)
{
    var->i++;
    var->j = var->i;
    Begin_Dolar(data,var);
    if(var->temp != NULL)
    {
        detect_dolar(var);
        free(var->temp);
        free(var->key);
        free(var->key_ex);
    }
    var->i = var->j;
    return(var->i);
}

void search_in_data(t_Dolar *var,char data_c,char *data)
{
    char* temp;

    temp = ft_strdup("");
    if(data_c != '$')
        quat_skip(&var->quat,data_c,&var->e); /* quat set*/
    else if(data_c == '$' && var->quat == '\'') /*when singelquet and dolar exest sqiping the key*/
    {
        temp[0] = data_c; 
        var->e = ft_strjoin(var->e,temp);
    }
    else if(data_c == '$')/*dolar in text or inter of doublequet*/
        var->i = Dolar(data,var);
    free(temp);
    temp = NULL;
}

void MakeKeyOfDlar(char *data,t_template **text,int branch)
{
    t_Dolar var;

    var.i = 0;
    var.e = ft_strdup("");
    var.expand = NULL;
    var.quat = 0;
    lstadd_back(&var.expand, new_template(new_expand("","")));
    while(var.i <= (int)ft_strlen(data))
    {
        search_in_data(&var,data[var.i],data);
        var.i++;
    }
    ExpandData(var.e,&var.expand,branch,text);
    free(var.e);
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
        MakeKeyOfDlar(((t_text*)lst->content)->data,&lst,TEXT);
		lst = lst->next;
	}
    return(0);
}

void ambiguous_redir(int *fd,char *file)
{
    printf("minishell: %s: ambiguous redirect\n",file);
    *fd = -1;
}

void generate_rederaction(int type,t_template *lst)
{
    if(type == TYPE_Rredirection)
    {
        if(((t_derections*)lst->content)->expand->next != NULL || ((t_ExpandData *)((t_derections*)lst->content)->expand->content)->expan_data[0] == '\0')
                ambiguous_redir(&((t_derections*)lst->content)->fd ,((t_derections*)lst->content)->file);
        else
            ((t_derections*)lst->content)->fd = open(((t_ExpandData *)((t_derections*)lst->content)->expand->content)->expan_data, O_WRONLY | O_CREAT | O_TRUNC, 0644);  //out >
    }
    if(type == TYPE_DRredirection)
    {
        if(((t_derections*)lst->content)->expand->next != NULL || ((t_ExpandData *)((t_derections*)lst->content)->expand->content)->expan_data[0] == '\0')
            ambiguous_redir(&((t_derections*)lst->content)->fd ,((t_derections*)lst->content)->file);
        else
            ((t_derections*)lst->content)->fd = open(((t_ExpandData *)((t_derections*)lst->content)->expand->content)->expan_data, O_WRONLY | O_CREAT | O_APPEND, 0644);  //out >>
    }
    if(type == TYPE_Lredirection)
    {
        if(((t_derections*)lst->content)->expand->next != NULL || ((t_ExpandData *)((t_derections*)lst->content)->expand->content)->expan_data[0] == '\0')
            ambiguous_redir(&((t_derections*)lst->content)->fd ,((t_derections*)lst->content)->file);
        else
        {
            ((t_derections*)lst->content)->fd = open(((t_derections*)lst->content)->file, O_RDONLY);
            if(((t_derections*)lst->content)->fd == -1)
                printf("minishell: %s: No such file or directory\n",((t_derections*)lst->content)->file);
        }
    }
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
        MakeKeyOfDlar(((t_derections*)lst->content)->file,&lst,DERECYION);
        generate_rederaction(((t_derections*)lst->content)->type,lst);
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
            return(1);
        lst = lst->next;
        if (r == 1 || r2 == 1)
            return(1);
    }
    return(0);
}
