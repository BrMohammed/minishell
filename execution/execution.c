# include "../minishell.h"

int *allocation_for_FD()
{
    int *fd;
    fd = (int *)malloc(sizeof(int) * 3);
    fd[2] = '\0';
    fd[1] = 0;
    fd[0] = 0;
    return(fd);
}

int *OutDerections(t_template* lst)
{
    t_template *tmp;
    int i;
    int *fd;
    
    i  = 0;
    fd = allocation_for_FD();
    tmp = lst;
    while (lst)
	{
        if(((t_derections*)lst->content)->file != NULL && ((t_derections*)lst->content)->type == TYPE_DLredirection)
            fd[0] = heredoc(((t_derections*)lst->content)->file);
		lst = lst->next;
	}
    while(tmp)
    {
        generate_rederaction(((t_derections*)tmp->content)->type,tmp);
        if(((t_derections*)tmp->content)->file != NULL && (((t_derections*)tmp->content)->type == TYPE_Rredirection || ((t_derections*)tmp->content)->type == TYPE_DRredirection))
            fd[1] = ((t_derections*)tmp->content)->fd; //out
        if(((t_derections*)tmp->content)->file != NULL && ((t_derections*)tmp->content)->type == TYPE_Lredirection)
            fd[0] = ((t_derections*)tmp->content)->fd;
        tmp = tmp->next;
    }
    return(fd);
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
void in_childe(t_template *lst,t_pMlist *pMlist_var,t_pipeline *var,int *pipe_exist)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    duplicate(var->fd_Der,pMlist_var->lastFd,lst,var->fd);
    if(*pipe_exist == 1 && pMlist_var->c != NULL)
        pMlist_var->enter_built = all_builtins(pMlist_var->c, *pipe_exist, var->fd[1]);
    if(pMlist_var->enter_built == 0)
    {
        if (execve(pMlist_var->path, &pMlist_var->c[0], g_global->envp) == -1)
        {
            printf("minishel: %s: command not found\n",pMlist_var->c[0]);
            exit(127);
        }
    }
}
int pipeline(t_template *lst,t_pMlist *pMlist_var)
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
            in_childe(lst,pMlist_var,&var,&pipe_exist);
    }
    close_parent(var,&pMlist_var->lastFd,lst);
    free(var.fd_Der);
    return(pMlist_var->lastFd);
}
