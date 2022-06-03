# include "../minishell.h"

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

int serch_on_env(char *c)
{
    int i;
    char *cr;
    int j;
    int x;

    i = 0;
    while(c[i] && c[i] != '=')
        i++;
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
    return (0);
}

char  **add_in_export(char **c)
{
    int i;
    int y;
    char **cr;
    int serch;
    int x;

    i = 1;
    serch = 0;
    x = 1;
    cr = NULL;
    while(c[x])
    { 
        serch = serch_on_env(c[x]);
        if(serch == 0)
            i++;
        x++;
    }
    x = 0;
    if(i != 1)
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
        while(c[y] != NULL)
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
    
    if(c[1] == '\0')
        just_export(fd,false);
    else
        g_global.envp = add_in_export(c);
    if(false == 1)
    {
        g_global.g_flags = 0;
        exit(0);
    }
}