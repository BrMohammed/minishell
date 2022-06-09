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

// void //signal_callback_handler(int sig)
// {
// 	(void)sig;
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	printf("\n");
// 	rl_redisplay();
// }

// void	signal_handler2(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 			ft_putchar_fd('\n', 1);
// 			rl_replace_line("", 0);
// 			rl_on_new_line();
// 			rl_redisplay();
// 	}
// 	else if (sig == SIGQUIT)
// 	{
// 		ft_putchar_fd('\r', 1);
// 		rl_on_new_line();
// 	}
// }

int main(int argc, char** argv, char** envp)
{
	char    *all;
	

	copie_env(envp);
	// signal(SIGQUIT, signal_handler);
	//signal(SIGINT, signal_handler2);
	(void)argv;
	(void) envp;
	all = ft_strdup("");
	if(argc == 1)
	{
		while (1 && all != NULL)
		{
			free(all);
			all = readline("minishell? ");
			add_history(all);	    
			if(all != NULL && all[0] != '\0')
				minishell(all);
		}
		free(all);
		free_table(g_global->envp);
	}
	return (0);
}