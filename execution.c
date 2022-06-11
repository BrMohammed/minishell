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
    int i;
    int *fd;
    
    i  = 0;
    fd = allocation_for_FD();
    while (lst)
	{
        exp = ((t_derections*)lst->content)->expand;
        if(((t_derections*)lst->content)->file != NULL && (((t_derections*)lst->content)->type == TYPE_Rredirection || ((t_derections*)lst->content)->type == TYPE_DRredirection))
            fd[1] = ((t_derections*)lst->content)->fd; //out
        if(((t_derections*)lst->content)->file != NULL && ((t_derections*)lst->content)->type == TYPE_DLredirection)
            fd[0] = heredoc(((t_derections*)lst->content)->file);
        if(((t_derections*)lst->content)->file != NULL && ((t_derections*)lst->content)->type == TYPE_Lredirection)
            fd[0] = ((t_derections*)lst->content)->fd;
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
    if(var.fd_Der[0] > 0)
        close(var.fd_Der[0]);
}

int  all_builtins(char **c, int pipe_exist, int fd)//?
{
    if(ft_strcmp(c[0],"export") == 0)
    {
        export(c,fd,pipe_exist);
        return(1);
    }
    if(ft_strcmp(c[0],"unset") == 0)
    {
        unset(c,pipe_exist);
        return(1);
    }
    if(ft_strcmp(c[0],"exit") == 0)
    {
        exitB(c);
        return(1);
    }
    if(ft_strcmp(c[0],"env") == 0)
    {
        envB(c,fd,pipe_exist);
        return(1);
    }
    if(ft_strcmp(c[0],"pwd") == 0)
    {
        pwd(c,fd,pipe_exist);
        return(1);
    }
    if (ft_strcmp(ft_tolower(c[0]),"echo") == 0)
    {
        echo(c,fd,pipe_exist);
        return(1);
    }
    if (ft_strcmp(c[0],"cd") == 0)
    {
        cd(c,pipe_exist);
        return(1);
    }
    return(0);
}

void piepe_exist_ans_der(int *pipe_exist,t_pipeline *var,t_pMlist *pMlist_var,t_template *lst)
{
    var->i  = 0;
    pMlist_var->enter_built = 0;
    *pipe_exist = 0;
    if(((t_Mlist *)lst->content)->derections)
        var->fd_Der = OutDerections(((t_Mlist *)lst->content)->derections);
    else
        var->fd_Der = allocation_for_FD();
    if (lst->next != NULL)
    {
        pipe( var->fd);
        *pipe_exist = 1;
    }
    if(*pipe_exist == 0 && pMlist_var->c != NULL &&  var->fd_Der[1] != -1 &&  var->fd_Der[0] != -1)
        pMlist_var->enter_built = all_builtins(pMlist_var->c, *pipe_exist,  var->fd[1]);
        
}

int pipeline(t_template *lst,t_pMlist *pMlist_var)//?
{
    t_pipeline var;
    int pipe_exist;

    piepe_exist_ans_der(&pipe_exist,&var,pMlist_var,lst);
    
    if(pMlist_var->enter_built == 0)
    {   
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        var.id = fork(); 
        if (var.id == 0)
        {  
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            duplicate(var.fd_Der,pMlist_var->lastFd,lst,var.fd);
            if(pipe_exist == 1 && pMlist_var->c != NULL)
                pMlist_var->enter_built = all_builtins(pMlist_var->c, pipe_exist, var.fd[1]);
            if(pMlist_var->enter_built == 0)
            {
                if (execve(pMlist_var->path, &pMlist_var->c[0], g_global->envp) == -1)
                {
                    printf("minishel: %s: command not found\n",pMlist_var->c[0]);
                    exit(127);
                }
            }
        } 
    }
    close_parent(var,&pMlist_var->lastFd,lst);
    free(var.fd_Der);
    return(pMlist_var->lastFd);
}
