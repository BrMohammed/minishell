# include "../minishell.h"

void print_env()
{
    int i;
    int y;
    int equal_exist;

    i = 0;
    equal_exist = 0;
    while (g_global->envp[i])
    {
        y = 0;
        equal_exist = 0;
        while(g_global->envp[i][y])
        {
            if(g_global->envp[i][y] == '=')
            {
                equal_exist = 1;
                break;
            }
            y++;
        }
        if(equal_exist == 1)
            printf("%s\n",g_global->envp[i]);
        i++;
    }
}

void envB(char **c,int fd,int false)
{
    int error;

    error = 0;
    if(c[1])
        error = args_error(c[1],1,"env");
    if(error == 0)
    {
        if(false == 1)
        dup2(fd,1);
        print_env();
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
