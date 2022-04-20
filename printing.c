# include "minishell.h"
# include "libft/libft.h"

void pText(void *content)
{
    printf("%s\n",((t_text*)content)->data);
}

void pDerections(void* content)
{
    if(((t_derections*)content)->file && ((t_derections*)content)->type)
	    printf("|%s, %d|\n",((t_derections*)content)->file,((t_derections*)content)->type);
}

void pMlist(void* content)
{
	lstiter(((t_Mlist *)content)->text,pText);
	lstiter(((t_Mlist *)content)->derections,pDerections);
}
