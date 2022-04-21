# include "minishell.h"
# include "libft/libft.h"

/***** ERROR *****/
void RText(void *content)
{
    printf("%s -> %d -> %d\n",((t_text*)content)->data, ((t_text*)content)->type,((t_text*)content)->order) ;
}

void RDerections(void* content)
{
    if(((t_derections*)content)->file && ((t_derections*)content)->type)
	    printf("|%s, %d , %d|\n",((t_derections*)content)->file,((t_derections*)content)->type,((t_derections*)content)->order);
}

void RMlist(void* content)
{
    if(((t_Mlist *)content)->text)
	    lstiter(((t_Mlist *)content)->text,RText);
    if(((t_Mlist *)content)->derections)
	    lstiter(((t_Mlist *)content)->derections,RDerections);
}

/***** PRINTING *****/
void pText(void *content)
{
    printf("%s -> %d -> %d\n",((t_text*)content)->data, ((t_text*)content)->type,((t_text*)content)->order) ;
}

void pDerections(void* content)
{
    if(((t_derections*)content)->file && ((t_derections*)content)->type)
	    printf("|%s, %d , %d|\n",((t_derections*)content)->file,((t_derections*)content)->type,((t_derections*)content)->order);
}

void pMlist(void* content)
{
    if(((t_Mlist *)content)->text)
	    lstiter(((t_Mlist *)content)->text,pText);
    if(((t_Mlist *)content)->derections)
	    lstiter(((t_Mlist *)content)->derections,pDerections);
}


