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
    char	**c;
    char	*path;
    int index;
    int t;
    int lastFd = -1;
    t_template *tmp = lst;
    int *fd_Der;

    index = 0;
    c = NULL;

    fd_Der = allocation_for_FD();
    while(lst)
    {
        path = NULL; 
        if(((t_Mlist *)lst->content)->derections && !((t_Mlist *)lst->content)->text)
        {
            fd_Der = OutDerections(((t_Mlist *)lst->content)->derections);
            if (fd_Der[1] != 0)
            {
                close(fd_Der[1]);
            }
            if (fd_Der[0] != 0)
            {
                close(fd_Der[0]);
            }
        }
        /**********   pipe  *********/
        if(((t_Mlist *)lst->content)->text)
        {
            c = pText(((t_Mlist *)lst->content)->text);
            if(c != NULL)
            {
                 path_finder(&path, c, g_global.envp);
                 lastFd = pipeline(lst,path,lastFd,c);
                if (path != NULL)
                    free(path);
                t = 0;
                while (c[t])
                    free(c[t++]);
            }
        }
        free(c);
       /*******************/

        index++;
        lst = lst->next;
    }
    while(tmp->next != NULL)
    {
        waitpid(((t_Mlist *)tmp->content)->pid, NULL, 0);
        tmp = tmp->next;
    }
    waitpid(((t_Mlist *)tmp->content)->pid, &g_global.g_flags, 0);
}