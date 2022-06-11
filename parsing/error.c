# include "../minishell.h"

int RText(t_template *lst,t_template *Mlst)
{
    (void)Mlst;
    while (lst)
	{
        if((((t_text*)lst->content)->data[0] == '|' && ((t_text*)lst->content)->order == 1))
        {
            printf("minishael :syntax error near unexpected token '%s'\n","|");
            return(1);
        }
        if(((t_text*)lst->content)->type == TYPE_ERROR)
        {
            printf("Syntax Error\n");
            return(1);
        }
        if((((t_text*)lst->content)->data[0] == '|' && lst->next == NULL))
            return(2);
        MakeKeyOfDlar(((t_text*)lst->content)->data,&lst,TEXT);
		lst = lst->next;
	}
    return(0);
}

void ambiguous_redir(int *fd,char *file)
{
    printf("minishell: %s: ambiguous redirect\n",file);
    *fd = -1;
}

void generate_rederaction(int type,t_template *lst)
{
    if(type == TYPE_Rredirection)
    {
        if(((t_derections*)lst->content)->expand->next != NULL || ((t_ExpandData *)((t_derections*)lst->content)->expand->content)->expan_data[0] == '\0')
                ambiguous_redir(&((t_derections*)lst->content)->fd ,((t_derections*)lst->content)->file);
        else
            ((t_derections*)lst->content)->fd = open(((t_ExpandData *)((t_derections*)lst->content)->expand->content)->expan_data, O_WRONLY | O_CREAT | O_TRUNC, 0644);  //out >
    }
    if(type == TYPE_DRredirection)
    {
        if(((t_derections*)lst->content)->expand->next != NULL || ((t_ExpandData *)((t_derections*)lst->content)->expand->content)->expan_data[0] == '\0')
            ambiguous_redir(&((t_derections*)lst->content)->fd ,((t_derections*)lst->content)->file);
        else
            ((t_derections*)lst->content)->fd = open(((t_ExpandData *)((t_derections*)lst->content)->expand->content)->expan_data, O_WRONLY | O_CREAT | O_APPEND, 0644);  //out >>
    }
    if(type == TYPE_Lredirection)
    {
        if(((t_derections*)lst->content)->expand->next != NULL || ((t_ExpandData *)((t_derections*)lst->content)->expand->content)->expan_data[0] == '\0')
            ambiguous_redir(&((t_derections*)lst->content)->fd ,((t_derections*)lst->content)->file);
        else
        {
            ((t_derections*)lst->content)->fd = open(((t_derections*)lst->content)->file, O_RDONLY);
            if(((t_derections*)lst->content)->fd == -1)
                printf("minishell: %s: No such file or directory\n",((t_derections*)lst->content)->file);
        }
    }
}
int RDerections(t_template* lst)
{
    char* t_temp;
    
    while (lst)
	{
        if(((t_derections*)lst->content)->type == TYPE_Lredirection)
            t_temp = "<";
        if(((t_derections*)lst->content)->type == TYPE_Rredirection)
            t_temp = ">";
        if(((t_derections*)lst->content)->type == TYPE_DLredirection)
            t_temp = "<<";
        if(((t_derections*)lst->content)->type == TYPE_DRredirection)
            t_temp = ">>";
        if(ft_strncmp(((t_derections*)lst->content)->file,"", 1) == 0 || ft_strncmp(((t_derections*)lst->content)->file,"|", 1) == 0)
        {
            printf("minishael :syntax error near unexpected token '%s'\n",t_temp);
            return(1);
        }
        MakeKeyOfDlar(((t_derections*)lst->content)->file,&lst,DERECYION);
        generate_rederaction(((t_derections*)lst->content)->type,lst);
		lst = lst->next;
	}
    return(3);
}

int RMlist(t_template* lst)
{
    int r;
    int r2;

    while(lst)
    { 
        r = 0;
        r2 = 0;
        if(((t_Mlist *)lst->content)->text)
	        r = RText(((t_Mlist *)lst->content)->text,lst);
        if(((t_Mlist *)lst->content)->derections)
	       r2 =  RDerections(((t_Mlist *)lst->content)->derections);
        
        if(r == 2 & r2 == 0)
            return(1);
        lst = lst->next;
        if (r == 1 || r2 == 1)
            return(1);
    }
    return(0);
}
