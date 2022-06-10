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

void	signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int main(int argc, char** argv, char** envp)
{
	char    *all;

	(void)argv;
	(void) envp;
	copie_env(envp);
	all = ft_strdup("");
	if(argc == 1)
	{
		while (1 && all != NULL)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, signal_handler2);
			free(all);
			g_global->error_her = 0;
			all = readline("minishell? ");
			add_history(all);	    
			if(all != NULL && all[0] != '\0')
				minishell(all);
		}
		free(all);
	}
	if(g_global->g_flags == 130)
		g_global->g_flags = 2;
	if(g_global->g_flags == 131)
		g_global->g_flags = 3;
	exit(g_global->g_flags);
}