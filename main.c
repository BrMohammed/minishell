#include "minishell.h"

int main(int argc, char** argv, char** envp)
{
	char    *all;
	
	g_global.envp = envp;
	g_global.g_flags = 0;
	(void)argv;
	(void) envp;
	if(argc == 1)
	{
		while (1)
		{
			all = readline("minishell? ");
			minishell(all);
			free(all);
		}
	}
	return (0);
}