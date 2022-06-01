# include "../minishell.h"

void exitB()
{
    g_global.g_flags = 0;
    exit(0);
}

void pwd(int fd,int false)
{
    int y;
    int i;

    y = 0;
    if(false == 1)
        dup2(fd,1);
    i = 0;
   while(g_global.envp[y] != NULL)
    {
        if(ft_strncmp(g_global.envp[y], "PWD",3) == 0)
            break;
        y++;
    }
    if(g_global.envp[y] != NULL)
    {
        while((g_global.envp[y][i] != '='))
            i++;
        if(g_global.envp[y][i] == '=')
        {
            while(g_global.envp[y][i + 1])
            {
                printf("%c",g_global.envp[y][i + 1]);
                i++;
            }
        }
        printf("\n");
    }
     if(false == 1)
    {
        g_global.g_flags = 0;
        exit(0);
    }
}

void envB(int fd,int false)
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
        equal_exist = 0;
        while(g_global.envp[i][y])
        {
            if(g_global.envp[i][y] == '=')
            {
                equal_exist = 1;
                break;
            }
            y++;
        }
        if(equal_exist == 1)
            printf("%s\n",g_global.envp[i]);
        i++;
    }
    if(false == 1)
    {
        g_global.g_flags = 0;
        exit(0);
    }
}