# include "../minishell.h"

void cd(char **c ,int false)
{
    //getcwd, chdir
    char cwd[256];
    if(c[1] != NULL)
    {        
        chdir(c[1]);
        getcwd(cwd, sizeof(cwd));
        printf("%s\n",cwd);
    }
    else
    {
        chdir(getenv("HOME"));
        getcwd(cwd, sizeof(cwd));
        printf("%s\n",cwd);
    }
        
    if(false == 1)
    {
        g_global.g_flags = 0;
        exit(0);
    }
}