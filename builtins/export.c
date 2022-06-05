# include "../minishell.h"
#include <errno.h>

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

void just_export(int fd,int false)
{
    int i;

    i = 0;
    if(false == 1)
        dup2(fd,1);
    while (g_global->envp[i])
    {
        print_export(g_global->envp[i]);
        i++;
    }
}

int input_error(char *c)
{
    if(c[0] == '-')
    {
        printf("minishell: export: `%c%c': invalid option\n",c[0],c[1]);
        g_global->g_flags = 4;
        return(1);
    }
    if((ft_isalnum(c) == 1 && ft_isdigit(c) == 0) || (c[0] >= '0' && c[0] <= '9'))
    {
        printf("minishell: export: `%s': not a valid identifier\n",c);
        g_global->g_flags = 1;
        return(1);
    }

    return(0);
}

int serch_on_env(char *c,int *error)
{
    int i;
    char *cr;
    int j;
    int x;
    char *befor_equal;

    i = 0;
   *error = 0;
    while(c[i] && c[i] != '=' )
        i++; 
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
        *error = input_error(befor_equal); //  error if input take 1 all the comm in the next dont export
        if(*error == 1)
        {
            free(befor_equal);
            return(1);
        }
        free(befor_equal);
    }
    if(c[i] == '\0')
    {
        i = 0;
        while (g_global->envp[i] && ft_strcmp(g_global->envp[i],c) != 0)
            i++;
        if(g_global->envp[i] != '\0')
            return(1);
    }
    else
    {
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
    }
    return (0);
}

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
}

void copie_table(char **cp)
{
    int i;

    i = 0;
    while(cp[i] != NULL)
		i++;
	g_global->envp = (char **)malloc(sizeof(char *) * i + 1);
	g_global->envp[i] = NULL;
    i = 0;
	while(cp[i] != NULL)
	{
		g_global->envp[i] = ft_strdup(cp[i]);
		i++;
	}
}

char **add_to_table(char *c)
{
    int i;
    char **cr;

    i = 0;
    while(g_global->envp[i])
        i++;
    cr = (char **)malloc(sizeof(char *) * (i + 2));
    cr[i + 1] = NULL;
    i = 0;
    while(g_global->envp[i] != NULL)
    {
        cr[i] = ft_strdup(g_global->envp[i]);
        i++;
    }
    cr[i] = ft_strdup(c);
    return(cr);
}

void add_in_export(char **c,int *error_out)
{
    char **cr;
    int serch;
    int x;
    int error;

    serch = 0;
    x = 1;
    error = 0;
    while(c[x])
    {  
        cr = NULL;
        serch = serch_on_env(c[x],&error);
        if(error == 1)
            *error_out = 1;
        if(serch == 0 && *error_out == 0)
        {
            cr = add_to_table(c[x]);
            free_table(g_global->envp);
            copie_table(cr);
            free_table(cr);
        }
        x++;
    }
}

void export(char **c,int fd,int false)
{
    int error;

    error = 0;
    if(c[1] == '\0')
        just_export(fd,false);
    else
        add_in_export(c,&error);
    if(false == 1)
    {
        if(error == 0)
            g_global->g_flags = 0;
        exit(0);
    }
}