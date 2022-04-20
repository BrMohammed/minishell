# include "minishell.h"
# include "libft/libft.h"

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
	lstiter(((t_Mlist *)content)->text,pText);
    if(((t_Mlist *)content)->derections)
	    lstiter(((t_Mlist *)content)->derections,pDerections);
}
