# include "minishell.h"
# include "libft/libft.h"

void pText(void *t)
{
	while (((t_text *)t)->data)
	{
		printf("%s\n", ((t_text *)((t_Mlist *)t)->text->content)->data);
	}
}

// void pRedit(void* content)
// {
// 	// if (asf>> ><<<)
// 	//     asdas
// }

void pMlist(void* content)
{
	lstiter(content,pText);
	//lstiter(redor, pRedit);
    //printf("%s\n",((t_text *)((t_Mlist *)list->content)->text->content)->data);
}
