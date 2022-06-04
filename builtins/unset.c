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

void unset(char **c,int false)
{
    int i;
    int y;
    int br;
    int error;
    int error_out;

    
    i = 0;
    error_out = 0;
    while(c[i + 1] != NULL)
    {
        error = input_error(c[i + 1]); //  error if input take 1 all the comm in the next dont export
        if(error == 1)
            error_out = 1;
        if(error_out == 0)
        {
             y = 0;
            br = 0;
            while(g_global->envp[y] != NULL)
            {
                if(ft_strncmp(g_global->envp[y], c[i + 1],ft_strlen(c[i + 1])) == 0 && 
                    (g_global->envp[y][ft_strlen(c[i + 1])] == '\0' || g_global->envp[y][ft_strlen(c[i + 1])] == '='))
                    break;
                y++;
                br = y;
            }
            if(g_global->envp[y] != NULL)
                unset_exist(br);
        }
        i++;
    }
    if(false == 1)
    {
        if(error == 0)
            g_global->g_flags = 0;
        exit(0);
    }
}