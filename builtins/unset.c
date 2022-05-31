# include "../minishell.h"

void unset(char **c,int false)
{
    int i;
    int y;
    char **cr;
    int comp;
    int br;

    
    i = 0;
    //cr = NULL;
    while(c[i + 1] != NULL)
    {
        comp = 0;
        y = 0;
        br = 0;
        while(g_global.envp[y] != NULL)
        {
            if(ft_strncmp(g_global.envp[y], c[i + 1],ft_strlen(c[i + 1])) == 0)
            {
               
                break;
            }
            y++;
            br = y;
        }
        if(g_global.envp[y] != NULL)
        {
            y = 0;
            while(g_global.envp[y])
                y++;
            y--;
            cr = (char **)malloc(sizeof(char *) * (y + 1));
            cr[y] = NULL;
            comp = 0;
            y = 0;
            
            while(g_global.envp[comp])
            {
                if(br != comp)
                {
                    cr[y] = ft_strdup(g_global.envp[comp]);
                    y++;
                }
                comp++;
            }
            g_global.envp = cr;
        }
        i++;
     }
    if(false == 1)
        exit(0);
}