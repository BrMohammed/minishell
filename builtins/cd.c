# include "../minishell.h"

void cd(char **c ,int false)
{
    //getcwd, chdir
    if(c[1] != NULL)
    {
        chdir(c[1]);
    }
        
    if(false == 1)
    {
        g_global.g_flags = 0;
        exit(0);
    }
}