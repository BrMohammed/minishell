# include "minishell.h"

void just_export(int fd,int false)
{
    int i;
    int y;

    i = 0;
    if(false == 1)
    {
        dup2(fd,1);
    }
    while (g_global.envp[i])
    {
        y = 0;
        while(g_global.envp[i][y])
        {
            if(y == 0)
                printf("declare -x ");
            printf("%c",g_global.envp[i][y]); 
            if(g_global.envp[i][y] == '=')
                printf("%c",'"');
            y++;
            if(g_global.envp[i][y] == '\0')
                printf("%c\n",'"');
        }
        i++;
    }
}

void export(char **c,int fd,int false)
{
    
    if(c[1] == '\0')
        just_export(fd,false);
    exit(0);
}