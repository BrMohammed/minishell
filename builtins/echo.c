# include "../minishell.h"

void echo(char **c,int fd,int false)
{
    int i;
    int y;
    int nl_exist;
    int skip;

    i = 0;
    y = 0;
    nl_exist = 1;
    skip = 1;
    if(false == 1)
        dup2(fd,1);
    while(c[i + 1])
    {
        if(c[1][0] == '-' && nl_exist == 1)
        {
            y = 1;
            while(c[1][y] && c[1][y] == 'n')
                y++;
            if(c[1][y] == '\0' && c[1][1] == 'n')
            {
                nl_exist = 0;
                i++;
            }
        }
        if(nl_exist == 0)
        {
            if(c[i + 1][0] == '-' && skip == 1)
            {  
                y = 1;
                while(c[i + 1][y] && c[i + 1][y] == 'n')
                    y++;
                if(c[i + 1][y] != '\0')
                    skip = 0;
            }
            else
                skip = 0;
            if(skip == 0 && c[i + 1] != NULL)
                printf("%s ",c[i + 1]);
        }
        else if(c[i + 1] != NULL)
            printf("%s ",c[i + 1]);
        i++;
    }
    if(nl_exist == 1)
       printf("\n");
    if(false == 1)
        exit(0);
}