# include "../minishell.h"
#include <errno.h>

void just_export(int fd,int false)
{
    int i;
    int y;
    int equal_exist; 

    i = 0;
    equal_exist = 0;
    if(false == 1)
        dup2(fd,1);
    while (g_global.envp[i])
    {
        y = 0;
        while(g_global.envp[i][y])
        {
            if(y == 0)
                printf("declare -x ");
            printf("%c",g_global.envp[i][y]); 
            if(g_global.envp[i][y] == '=')
            {
                printf("%c",'"');
                equal_exist = 1;
            }
            y++;
            if(g_global.envp[i][y] == '\0' && equal_exist == 1)
            {
                printf("%c",'"');
                equal_exist = 0;
            }
            if (g_global.envp[i][y] == '\0')
                printf("\n");
        }
        i++;
    }
}

int input_error(char c,char *arg)
{
    if(arg[0] == '-')
    {
        printf("minishell: export: `%c%c': invalid option\n",arg[0],arg[1]);
        g_global.g_flags = 4;
        return(1);
    }
    if(ft_isalnum(c) == 0)
    {
        printf("minishell: export: `%s': not a valid identifier\n",arg);
        g_global.g_flags = 1;
        return(1);
    }
    return(0);
}

int serch_on_env(char *c,int *error)
{
    int i;
    char *cr;
    int j;
    int x;
    int error_out;

    i = 0;
   *error = 0;
   error_out = 0;
    while(c[i] && c[i] != '=' )
    {
        *error = input_error(c[i],c); //  error if input take 1 all the comm in the next dont export
        if(*error == 1)
            error_out = 1;
        if(error_out == 1)
        {
            return(1);
        }
        i++; 
    }
    if(*error == 0)
    {
            if(c[i] == '\0')
        {
            i = 0;
            while (g_global.envp[i] && ft_strcmp(g_global.envp[i],c) != 0)
                i++;
            if(g_global.envp[i] != '\0')
                return(1);
        }
        else
        {
            x = i;
            i = 0;
            while (g_global.envp[i] && ft_strncmp(g_global.envp[i],c, x) != 0)
                i++;
            if(g_global.envp[i] != '\0')
            {
                cr = malloc(sizeof(char*) * ft_strlen(c)+1);
                cr[ft_strlen(c)] = '\0';
                j = 0;
                while(c[j])
                {
                    cr[j] = c[j];
                    j++;
                }
                g_global.envp[i] = cr;
                return(1);
            }
        }
    }
    
    return (0);
}

char  **add_in_export(char **c,int *error_out)
{
    int i;
    int y;
    char **cr;
    int serch;
    int x;
    int error;

    i = 1;
    serch = 0;
    x = 1;
    cr = NULL;
    error = 0;
    while(c[x])
    { 
        serch = serch_on_env(c[x],&error);
        if(serch == 0)
            i++;
        x++;
    }
    if(error == 1)
        *error_out = 1;
    x = 0;
    if(i != 1 && error == 0 && *error_out == 0)
    {
        while(g_global.envp[x])
            x++;
        cr = (char **)malloc(sizeof(char *) * (x + i + 1));
        cr[x + i] = NULL;
        i = 0;
        while(g_global.envp[i] != NULL)
        {
            cr[i] = ft_strdup(g_global.envp[i]);
            i++;
        }
        y = 0;
        while(c[y] != NULL && y <= x)
        {
            if(c[y + 1] != '\0')
                cr[i] = ft_strdup(c[y + 1]);
            i++;
            y++;
        }
        return(cr);
    }
    return(g_global.envp);
}

void export(char **c,int fd,int false)
{
    int error;

    error = 0;
    if(c[1] == '\0')
        just_export(fd,false);
    else
        g_global.envp = add_in_export(c,&error);
    printf("%d\n",error);
    if(false == 1)
    {
        if(error == 0)
            g_global.g_flags = 0;
        exit(0);
    }
}