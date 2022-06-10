# include "../minishell.h"

void nl_not_exist(int *nl_exist,char **c,int *i)
{
    int y;

    if(c[1][0] == '-' && *nl_exist == 1)
    {
        y = 1;
        while(c[1][y] && c[1][y] == 'n')
            y++;
        if(c[1][y] == '\0' && c[1][1] == 'n')
        {
            *nl_exist = 0;
            *i = *i + 1;
        }
    }
}

void nl__exist(int nl_exist,int *skip,char *c)
{
    int y;
    if(nl_exist == 0)
    {
        if(c[0] == '-' && *skip == 1)
        {  
            y = 1;
            while(c[y] && c[y] == 'n')
                y++;
            if(c[y] != '\0')
                skip = 0;
        }
        else
            skip = 0;
        if(skip == 0 && c != NULL)
            printf("%s ",c);
    }
    else if(c != NULL)
        printf("%s ",c);
}

void echo(char **c,int fd,int false)
{
    int i;
    int nl_exist;
    int skip;

    i = 0;
    nl_exist = 1;
    skip = 1;
    if(false == 1)
        dup2(fd,1);
    while(c[i + 1])
    {
        nl_not_exist(&nl_exist,c,&i);
        nl__exist(nl_exist,&skip,c[i + 1]);
        i++;
    }
    if(nl_exist == 1)
       printf("\n");
    if(false == 1)
    {
        g_global->g_flags = 0;
        exit(0);
    }
    else
        g_global->g_flags = 0;
}