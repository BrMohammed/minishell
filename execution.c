# include "minishell.h"

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
    fd = (int *)malloc(sizeof(int) * 3);
    fd[2] = '\0';
	if (!fd)
		return (0);

    fd[0]= 0;
    fd[1] = 0;
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

int pipeline(t_template *lst,char *path, int lastFd,char **c)
{
    int fd[2];
    int *fd_Der;
    int id;
    int i;
    
    i  = 0;
    fd_Der = (int *)malloc(sizeof(int) * 3);
    fd_Der[2] = '\0';
	if (!fd_Der)
		return (0);
    fd_Der[1] = 0;
    fd_Der[0] = 0;
    if(((t_Mlist *)lst->content)->derections)
       fd_Der = OutDerections(((t_Mlist *)lst->content)->derections);
    if (lst->next != NULL)
        pipe(fd);
    id = fork();
    if (id == 0)
    {  
        if(fd_Der[0] == -1 || fd_Der[1] == -1)
        {
            exit(1);
        }
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
        if (execve(path, &c[0], g_global.envp) == -1)
        {
            perror(c[0]);
            exit(1);
        }
        close(fd[0]);
    }
    else
    {
       ((t_Mlist *)lst->content)->pid = id;
        if(lastFd != -1)
            close(lastFd);
        lastFd = fd[0];
        if (lst->next != NULL)
            close(fd[1]);
        if(fd_Der[1] > 0)
            close(fd_Der[1]);
        if(fd_Der[0] > 0 )
            close(fd_Der[0]);
    }
    return(lastFd);
}
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

char **pDerections(t_template* lst)
{
    t_template *exp;

    while (lst)
	{
        exp = ((t_derections*)lst->content)->expand;
         if(((t_derections*)lst->content)->file != NULL && ((t_derections*)lst->content)->type)
         {
            //printf(" |%s, type : %d , ord : %d , fd : %d| (>>) ",((t_derections*)lst->content)->file,((t_derections*)lst->content)->type,((t_derections*)lst->content)->order,((t_derections*)lst->content)->fd);
         }
	        
         while(exp) /*   >>>>>   for looping in the expanded link of node text*/
        { 
            //printf("{%s ==>> %s}",((t_ExpandData*)exp->content)->expan_data,((t_ExpandData*)exp->content)->key);
            exp = exp->next;
        }
		lst = lst->next;
	}
    return(0);
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

     fd_Der = (int *)malloc(sizeof(int) * 3);
    fd_Der[2] = '\0';
    fd_Der[1] = 0;
    fd_Der[0] = 0;
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
    int ex;
    int lastone;
    while(tmp->next != NULL)
    {
        waitpid(((t_Mlist *)tmp->content)->pid, &ex, 0);
        tmp = tmp->next;
    }
    waitpid(((t_Mlist *)tmp->content)->pid, &lastone, 0);
    // echo $?
}