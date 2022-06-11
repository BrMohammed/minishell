# include "../minishell.h"

void free_table(char **c)
{
    int i;

    i = 0;
    while(c[i])
    {
        free(c[i]);
        i++;
    }
    free(c);
    c = NULL;
}

void copie_table(char **cp)
{
    int i;

    i = 0;
    while(cp[i])
		i++;
	g_global->envp = (char **)malloc(sizeof(char *) * i + 1);
    i = 0;
	while(cp[i])
	{
		g_global->envp[i] = ft_strdup(cp[i]);
		i++;
	}
    g_global->envp[i] = NULL;
}

int errorin_args(char *c,int error,int i)
{
    char *befor_equal;
    int j;

    if(c)
    {
        j = 0;
        befor_equal = malloc(i);
        if(!befor_equal)
            return(0);
        befor_equal[i] = '\0';
        while(c[j] && j < i)
        {
            befor_equal[j] = c[j];
            j++;
        }
        error = input_error(befor_equal); //  error if input take 1 all the comm in the next dont export
        if(error == 1)
        {
            free(befor_equal);
            return(1);
        }
        free(befor_equal);
    }
    return(0);
}

int replace(int i,char *c)
{
    char *cr;
    int x;
    int j;

    x = i;
    i = 0;
    while (g_global->envp[i] && ft_strncmp(g_global->envp[i],c, x) != 0)
        i++;
    if(g_global->envp[i] != '\0')
    {
        cr = malloc(sizeof(char*) * ft_strlen(c)+1);
        cr[ft_strlen(c)] = '\0';
        j = 0;
        while(c[j])
        {
            cr[j] = c[j];
            j++;
        }
        free(g_global->envp[i]);
        g_global->envp[i] = ft_strdup(cr);
        free(cr);
        return(1);
    }
    return(0);
}

void print_export(char *c)
{
    int equal_exist;
    int y;

    equal_exist = 0;
    y = 0;
    while(c[y])
    {
        if(y == 0)
            printf("declare -x ");
        printf("%c",c[y]); 
        if(c[y] == '=')
        {
            printf("%c",'"');
            equal_exist = 1;
        }
        y++;
        if(c[y] == '\0' && equal_exist == 1)
        {
            printf("%c",'"');
            equal_exist = 0;
        }
        if (c[y] == '\0')
            printf("\n");
    }
}