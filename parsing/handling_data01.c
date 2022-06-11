# include "../minishell.h"


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

void finde_another_arg(t_Dolar *var,int *t)
{
    t_template *temp00;

    temp00 = NULL;
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
    while(var->key[*t] == 32)
        *t = *t + 1;;
}

void DolarWhoutQuat(t_Dolar *var)
{
    int t;
    char *for_expand;

    for_expand = malloc(2);
    for_expand[1] = '\0';
    t = 0;
    while(var->key[t] != '\0' )
    {
        for_expand[0] = var->key[t];
        var->e = ft_strjoin(var->e,for_expand);
        t++;
        if(var->key[t] == 32)
            finde_another_arg(var,&t);
    }
    free(for_expand);
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