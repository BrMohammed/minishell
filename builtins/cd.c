# include "../minishell.h"

void cd(char **c ,int false)
{
    //getcwd, chdir
    char cwd[256];
    char *old;
    char **temp;

    temp = malloc(3);
    temp[2] = NULL;
    old = ft_strdup("OLDPWD=");
    temp[0] = ft_strdup("export");
    if(c[1] != NULL)
    {        
        getcwd(cwd, sizeof(cwd));
        old = ft_strjoin(old,cwd);
        temp[1] = ft_strdup(old);
        export(temp,0,0);
        free(old);
        free(temp[1]);
        chdir(c[1]);
        old = ft_strdup("PWD=");
        getcwd(cwd, sizeof(cwd));
        old = ft_strjoin(old,cwd);
        temp[1] = ft_strdup(old);
        export(temp,0,0);
    }
    else
    {
        chdir(getenv("HOME"));
        getcwd(cwd, sizeof(cwd));
    }
        
    if(false == 1)
    {
        g_global.g_flags = 0;
        exit(0);
    }
}