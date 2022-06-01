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

void add_in_export(char **c)
{
    int i;
    int y;
    char **cr;

    i = 0;
    while(c[i])
        i++;
    i--;
    while(g_global.envp[i])
        i++;
    cr = (char **)malloc(sizeof(char *) * (i + 1));
    cr[i] = NULL;
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
    g_global.envp = cr;
}

void export(char **c,int fd,int false)
{
    
    if(c[1] == '\0')
        just_export(fd,false);
    else
        add_in_export(c);
     if(false == 1)
    {
        g_global.g_flags = 0;
        exit(0);
    }
}