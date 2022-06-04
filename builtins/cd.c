# include "../minishell.h"

void move_to_dir(char *c)
{
    char cwd[256];
    char *old;
    char **temp;

    temp = malloc(3);
    temp[2] = NULL;
    old = ft_strdup("OLDPWD=");
    temp[0] = ft_strdup("export");
    getcwd(cwd, sizeof(cwd));
    old = ft_strjoin(old,cwd);
    temp[1] = ft_strdup(old);
    export(temp,0,0);
    free(old);
    free(temp[1]);
    chdir(c);
    old = ft_strdup("PWD=");
    getcwd(cwd, sizeof(cwd));
    old = ft_strjoin(old,cwd);
    temp[1] = ft_strdup(old);
    export(temp,0,0);
}

void cd(char **c ,int false)
{
    
    if(c[1] != NULL)
        move_to_dir(c[1]);
    else
        move_to_dir(getenv("HOME"));
    if(false == 1)
    {
        g_global.g_flags = 0;
        exit(0);
    }
}