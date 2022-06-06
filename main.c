#include "minishell.h"

void copie_env(char **envp)
{
	int i;

	i = 0;
	g_global = malloc(sizeof(t_global));
	while(envp[i] != NULL)
		i++;
	g_global->envp = (char **)malloc(sizeof(char *) * (i + 1));
	g_global->envp[i] = NULL;
	i = 0;
	while(envp[i] != NULL)
	{
		g_global->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	g_global->g_flags = 0;
}

int main(int argc, char** argv, char** envp)
{
	char    *all;
	
	copie_env(envp);
	(void)argv;
	(void) envp;
	if(argc == 1)
	{
		while (1)
		{
			all = readline("minishell? ");
			add_history(all);
			minishell(all);
			free(all);
		}
		free_table(g_global->envp);
	}
	return (0);
}