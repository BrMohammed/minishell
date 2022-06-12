# include "../minishell.h"

int	*allocation_for_fd(void)
{
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 3);
	fd[2] = '\0';
	fd[1] = 0;
	fd[0] = 0;
	return (fd);
}

int *out_derections(t_template* lst, int *interpted)
{
	t_template	*tmp;
	int			i;
	int			*fd;

	i = 0;
	fd = allocation_for_fd();
	tmp = lst;
	while (lst)
	{
		if (((t_derections *)lst->content)->file != NULL
			&& ((t_derections *)lst->content)->type == TYPE_DLredirection)
			fd[0] = heredoc(((t_derections *)lst->content)->file, interpted);
		lst = lst->next;
	}
	while (tmp && *interpted != 1)
	{
        fd_of_redir(tmp, fd, interpted);
		tmp = tmp->next;
	}
	return (fd);
}

void piepe_exist_ans_der(int *pipe_exist,t_pipeline *var,t_pmlist *pmlist_var,t_template *lst)
{
    var->i  = 0;
    pmlist_var->enter_built = 0;
    *pipe_exist = 0;
    if(((t_Mlist *)lst->content)->derections)
        var->fd_Der = out_derections(((t_Mlist *)lst->content)->derections,&var->interpted);
    else
        var->fd_Der = allocation_for_fd();
    if (lst->next != NULL)
    {
        pipe( var->fd);
        *pipe_exist = 1;
    }
    
    if(*pipe_exist == 0 && pmlist_var->c != NULL &&  var->fd_Der[1] != -1 &&  var->fd_Der[0] != -1)
        pmlist_var->enter_built = all_builtins(pmlist_var->c, *pipe_exist,  var->fd[1]);
}
void in_childe(t_template *lst,t_pmlist *pmlist_var,t_pipeline *var,int *pipe_exist)
{
    if(var->interpted == 1)
        exit(1);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    duplicate(var->fd_Der,pmlist_var->lastFd,lst,var->fd);
    if(*pipe_exist == 1 && pmlist_var->c != NULL)
        pmlist_var->enter_built = all_builtins(pmlist_var->c, *pipe_exist, var->fd[1]);
    if(pmlist_var->enter_built == 0)
    {
        if (execve(pmlist_var->path, &pmlist_var->c[0], g_global->envp) == -1)
        {
            printf("minishel: %s: command not found\n",pmlist_var->c[0]);
            exit(127);
        }
    }
}
int pipeline(t_template *lst,t_pmlist *pmlist_var)
{
    t_pipeline var;
    int pipe_exist;

    var.interpted = 0;
    piepe_exist_ans_der(&pipe_exist,&var,pmlist_var,lst);
    if(pmlist_var->enter_built == 0)
    {   
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        var.id = fork(); 
        if (var.id == 0)
            in_childe(lst,pmlist_var,&var,&pipe_exist);
    }
    close_parent(var,&pmlist_var->lastFd,lst);
    free(var.fd_Der);
    return(pmlist_var->lastFd);
}
