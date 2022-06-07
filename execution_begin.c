# include "minishell.h"

char** pText(t_template* lst)
{
    t_template *exp;
    int number_of_cases;
    char **c;

    c = creat_table(lst);
    number_of_cases = 0;
    while (lst)
	{
        exp = ((t_text*)lst->content)->expand;
        if(((t_text*)lst->content)->data != NULL)
        {
            //printf("{%s -> type : %d -> ord : %d} (>>) ",((t_text*)lst->content)->data, ((t_text*)lst->content)->type,((t_text*)lst->content)->order);
        }
            
        while(exp) /*   >>>>>   for looping in the expanded link of node text*/
        { 
            //printf("{%s ==>> %s}",((t_ExpandData*)exp->content)->expan_data,((t_ExpandData*)exp->content)->key);
            if(ft_strncmp(((t_ExpandData*)exp->content)->expan_data, "|",1) != 0)
            {
                c[number_of_cases] = ft_strdup(((t_ExpandData*)exp->content)->expan_data);
                number_of_cases++;
            }
            exp = exp->next;
        }
		lst = lst->next;
	}
    return(c);
}

void pMlist(t_template* lst)
{
    t_pMlist pMlist_var;
    t_template *tmp; 
    //int *fd_Der;

    tmp = lst;
    pMlist_var.lastFd = -1;
   
    while(lst)
    {
        pMlist_var.c = NULL;
        pMlist_var.path = NULL;
        if(((t_Mlist *)lst->content)->text || ((t_Mlist *)lst->content)->derections)
        {
            pMlist_var.c = pText(((t_Mlist *)lst->content)->text);
            if(pMlist_var.c != NULL)
            {
                path_finder(&pMlist_var.path, pMlist_var.c, g_global->envp);
            }
            pMlist_var.lastFd = pipeline(lst,&pMlist_var);
            if (pMlist_var.path != NULL)
                free(pMlist_var.path);
            if (pMlist_var.c != NULL)
                free_table(pMlist_var.c);
        }
        lst = lst->next;
    }
    while(tmp->next != NULL)
    {
        waitpid(((t_Mlist *)tmp->content)->pid, NULL, 0);
        tmp = tmp->next;
    }
    if(pMlist_var.enter_built == 0)
    {
        waitpid(((t_Mlist *)tmp->content)->pid, &g_global->g_flags, 0);
        g_global->g_flags = WEXITSTATUS(g_global->g_flags);
    }
    else
        waitpid(((t_Mlist *)tmp->content)->pid, NULL, 0);
}