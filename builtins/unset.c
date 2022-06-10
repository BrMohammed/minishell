# include "../minishell.h"

void unset_exist(int br)
{
    int y;
    char **cr;
    int comp;

    y = 0;
    while(g_global->envp[y])
        y++;
    y--;
    cr = (char **)malloc(sizeof(char *) * (y + 1));
    cr[y] = NULL;
    comp = 0;
    y = 0;
    while(g_global->envp[comp])
    {
        if(br != comp)
        {
            cr[y] = ft_strdup(g_global->envp[comp]);
            y++;
        }
        comp++;
    }
    free_table(g_global->envp);
    copie_table(cr);
    free_table(cr);
}

void delete(int *error,int *error_out,char *c)
{
    int y;
    int br;

    if(*error == 1)
        *error_out = 1;
    if(*error_out == 0)
    {
            y = 0;
        br = 0;
        while(g_global->envp[y] != NULL)
        {
            if(ft_strncmp(g_global->envp[y], c,ft_strlen(c)) == 0 && 
                (g_global->envp[y][ft_strlen(c)] == '\0' || g_global->envp[y][ft_strlen(c)] == '='))
                break;
            y++;
            br = y;
        }
        if(g_global->envp[y] != NULL)
            unset_exist(br);
    }
}

void unset(char **c,int false) 
{
    int i;
    int error;
    int error_out;

    i = 0;
    error_out = 0;
    while(c[i + 1] != NULL)
    {
        error = input_error(c[i + 1]); //  error if input take 1 all the comm in the next dont export
        delete(&error,&error_out,c[i + 1]);
        i++;
    }
    if(false == 1)
    {
        if(error == 0)
            g_global->g_flags = 0;
        exit(g_global->g_flags);
    }
    if(error == 0)
        g_global->g_flags = 0;
}