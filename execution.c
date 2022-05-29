# include "minishell.h"

int *allocation_for_FD()
{
    int *fd;
    fd = (int *)malloc(sizeof(int) * 3);
    fd[2] = '\0';
    fd[1] = 0;
    fd[0] = 0;
    return(fd);
}

char **creat_table(t_template *lst)
{
    t_template* temp_exp;
    int number_of_cases;
    char **c;

    c = NULL;
    number_of_cases = 0;
    while (lst)
	{
        temp_exp = ((t_text*)lst->content)->expand;
        while(temp_exp)
        {
            if(ft_strncmp(((t_ExpandData*)lst->content)->expan_data, "|",1) != 0)
                number_of_cases++;
            temp_exp = temp_exp->next;
        }
		lst = lst->next;
	}
    if(number_of_cases != 0)
    {
        c = (char **)malloc(sizeof(char *) * (number_of_cases + 1));
        c[number_of_cases] = NULL;
    }
    return(c);
}

int *OutDerections(t_template* lst)
{
    t_template *exp;
    int *fd;
    int i;
    int used[2];
    
    i  = 0;
    used[1] = 0;
    used[0] = 0;
    fd = allocation_for_FD();
    while (lst)
	{
        exp = ((t_derections*)lst->content)->expand;
        if(((t_derections*)lst->content)->file != NULL && (((t_derections*)lst->content)->type == TYPE_Rredirection || ((t_derections*)lst->content)->type == TYPE_DRredirection))
        {
             if(used[1] % 2 == 1)
            {
                close(fd[1]);
                used[1]++;
            }
            fd[1] = ((t_derections*)lst->content)->fd; //out
            if(fd[1] == -1)
                printf("minishell: %s: Permission denied \n",((t_derections*)lst->content)->file);
            used[1]++;
        }  
        if(((t_derections*)lst->content)->file != NULL && ((t_derections*)lst->content)->type == TYPE_DLredirection)
        {
            if(used[0] % 2 == 1)
            {
                close(fd[0]);
                used[0]++;
            }
            fd[0] = heredoc(((t_derections*)lst->content)->file);
            used[0]++;
        }
            
        if(((t_derections*)lst->content)->file != NULL && ((t_derections*)lst->content)->type == TYPE_Lredirection)
        {
            if(used[0] % 2 == 1)
            {
                close(fd[0]);
                used[0]++;
            }
            fd[0] = ((t_derections*)lst->content)->fd;
            used[0]++;
        }
		lst = lst->next;
	}
    return(fd);
}

void duplicate(int *fd_Der,int lastFd,t_template *lst,int *fd)
{
    if(fd_Der[0] == -1 || fd_Der[1] == -1)
        exit(1);
    if(fd_Der[0] > 0)
    {
        dup2(fd_Der[0], 0);
        close(fd_Der[0]);
    }
    else if (lastFd != -1)
    {
        dup2(lastFd, 0);
        close(lastFd);
    }
    if(fd_Der[1] > 0)
    {
        dup2(fd_Der[1], 1);
        close(fd_Der[1]);
    }
    else if (lst->next != NULL)
    {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
    }
}

void close_parent(t_pipeline var,int *lastFd,t_template *lst)
{
    ((t_Mlist *)lst->content)->pid = var.id;
    if(*lastFd != -1)
        close(*lastFd);
    *lastFd = var.fd[0];
    if (lst->next != NULL)
        close(var.fd[1]);
    if(var.fd_Der[1] > 0)
        close(var.fd_Der[1]);
    if(var.fd_Der[0] > 0 )
        close(var.fd_Der[0]);
}



int pipeline(t_template *lst,char *path, int lastFd,char **c)
{
    t_pipeline var;
    
    var.i  = 0;
    var.fd_Der = allocation_for_FD();
    if(((t_Mlist *)lst->content)->derections)
       var.fd_Der = OutDerections(((t_Mlist *)lst->content)->derections);
    if (lst->next != NULL)
        pipe(var.fd);
    var.id = fork();
    if (var.id == 0)
    {  
        duplicate(var.fd_Der,lastFd,lst,var.fd);
        if (execve(path, &c[0], g_global.envp) == -1)
        {
            perror(c[0]);
            exit(1);
        }
    }
    else
        close_parent(var,&lastFd,lst);
    return(lastFd);
}
