# include "../minishell.h"

int args_error(char *c,int false,char *name)
{
    if(c[0] == '-')
    {
        printf("%s: `%c%c': put commend without option\n",name,c[0],c[1]);
        g_global->g_flags = 1;
        return(1);
    }
    else if(false == 1)
    {
        printf("%s: `%s': put commend without args \n",name,c); 
        g_global->g_flags = 1;
        return(1);
    }
    return(0);
}

/*************** --  exit -- ******************/
void exitB(char **c)
{
    int error;

    error = 0;
    printf("exit\n");
    if(c[1])
        error = args_error(c[1],1,"exit");
    if(error == 0)
    {
        g_global->g_flags = 0;
        exit(0);
    }
    else
    {
        g_global->g_flags = 1;
        exit(0);
    }
}

/*************** --  pwd -- ******************/

void shearch_and_print()
{
    int y;
    int i;

    y = 0;
    i = 0;
    while(g_global->envp[y] != NULL)
    {
        if(ft_strncmp(g_global->envp[y], "PWD",3) == 0)
            break;
        y++;
    }
    if(g_global->envp[y] != NULL)
    {
        while((g_global->envp[y][i] != '='))
            i++;
        if(g_global->envp[y][i] == '=')
        {
            while(g_global->envp[y][i + 1])
            {
                printf("%c",g_global->envp[y][i + 1]);
                i++;
            }
        }
        printf("\n");
    }
}

void pwd(char **c,int fd,int false)
{
    int error;

    error = 0;
    if(c[1])
        error = args_error(c[1],0,"pwd");
    if(error == 0)
    {
        if(false == 1)
            dup2(fd,1);
        shearch_and_print();
    }
    if(false == 1)
    {
        if(error == 0)
            g_global->g_flags = 0;
        exit(0);
    }
}

/*************** --  env -- ******************/

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
        exit(0);
    }
}