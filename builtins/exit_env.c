# include "../minishell.h"

void exitB()
{
    exit(0);
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
        exit(0);
}