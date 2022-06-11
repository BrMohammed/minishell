# include "../minishell.h"

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