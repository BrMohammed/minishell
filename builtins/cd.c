# include "../minishell.h"

int move_to_dir(char *c)
{
    char cwd[256];
    char *old;
    char **temp;
    DIR *dir;

    if ((dir = opendir (c)) == NULL) 
    {
        printf("minishael: cd: %s: No such file or directory\n",c);
        g_global->g_flags = 1;
        closedir(dir);
        return(1);
    }
    closedir(dir);
    
    temp = (char **)malloc(sizeof(char *) * 3);
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
    free_table(temp);
    temp = NULL;
    free(old);
    old = NULL;
    return (0);
}

void cd(char **c ,int false)
{
    int i;
    int error;

    i = 0;
    error = 0;
    if(c[1] != NULL)
        error = move_to_dir(c[1]);
    else if (c[1] == NULL)
        error = move_to_dir(getenv("HOME"));
    if(false == 1)
    {
       if(error == 0)
            g_global->g_flags = 0;
        exit( g_global->g_flags);
    }
    if(error == 0)
        g_global->g_flags = 0;
}
