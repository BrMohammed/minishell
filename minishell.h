/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:38:48 by brmohamm          #+#    #+#             */
/*   Updated: 2022/06/14 06:10:28 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>

# define TEXT  1
# define DERECYION 0

typedef struct s_global
{
	char	**envp;
	int		g_flags;
	int		error_her;
}t_global;

t_global	*g_global;

typedef struct s_pipeline
{
	int	fd[2];
	int	*fd_der;
	int	id;
	int	i;
	int	interpted;
}t_pipeline;

typedef struct s_pmlist
{
	char	**c;
	char	*path;
	int		lastfd;
	int		enter_built;
}t_pmlist;

typedef struct s_template
{
	void				*content;
	struct s_template	*next;
	struct s_template	*prev;
}t_template;

typedef struct s_token
{
	char	*value;
	enum
	{
		TYPE_TEXT ,
		TYPE_QUOTE,
		TYPE_DLredirection,
		TYPE_DRredirection,
		TYPE_Lredirection,
		TYPE_Rredirection,
		TYPE_PIPE,
		TYPE_EOF,
		TYPE_ERROR,
	}e_type;
}t_token;

typedef struct s_lexer
{
	char			*src;
	unsigned int	size;
	unsigned int	i;
	char			c;

}t_lexer;

typedef struct s_expand_data
{
	char	*expan_data;
	char	*key;
}t_expand_data;

typedef struct s_text
{
	char		*data;
	t_template	*expand;
	int			order;
	int			type;
}t_text;

typedef struct s_derections
{
	char		*file;
	t_template	*expand;
	int			order;
	int			type;
	int			fd;
}t_derections;

typedef struct s_Mlist
{
	t_template	*text;
	t_template	*derections;
	pid_t		pid;
	int			order;
}t_Mlist;

typedef struct s_makelist
{
	t_token		*token;
	t_template	*text;
	t_template	*derections;
	int			i;
	int			i2;
	char		*temp2;
	int			temp;
}t_makelist;

typedef struct s_dolar
{
	int			i;
	int			j;
	char		*e;
	char		quat;
	t_template	*expand;
	char		*temp;
	char		*key_ex;
	char		*key;
}t_dolar;

t_token			*init_token(char *value, int type);
t_lexer			*init_lexer(char *src);
t_token			*get_next_token(t_lexer *lexer);

t_template		*new_template(void *content);
void			lstadd_back(t_template **lst, t_template *new);
t_template		*lstlast(t_template *lst);
void			lstiter(t_template *lst, void (*f)(void *));

t_Mlist			*new_list( t_template *text, t_template *derections, int order);
t_derections	*new_derections(char *file, int type, int order);
t_text			*new_text(char *data, int type, int order);
t_expand_data	*new_expand(char *expand_data, char*key);

void			*minishell(char *all);
void			pmlist(t_template *lst);
int				rmlist(t_template *lst);
void			make_key_of_dolar(char *data, t_template **text, int branch);
void			begin_dolar(char *data, t_dolar *var);
void			detect_dolar(t_dolar *var);
void			if_dolar_in_env(char *data, t_dolar *var);
int				all_builtins(char **c, int pipe_exist, int fd, t_pipeline *var);
void			duplicate(int *fd_der, int lastfd, t_template *lst, int *fd);
void			close_parent(t_pipeline *var, int *lastfd, t_template *lst);
void			path_finder(char **path, char **c, char **envp);
int				pipeline(t_template *lst, t_pmlist *pmlist_var,
					t_pipeline *var, int pipe_exist);
char			**creat_table(t_template *lst);
int				heredoc(char *file, int *error);
int				main(int argc, char **argv, char **envp);
int				*allocation_for_fd(void);
int				*out_derections(t_template *lst, int *interpted);
void			export(char **c, int fd, int false, t_pipeline *var);
void			print_export(char *c, t_pipeline *var);
void			unset(char **c, int false);
void			exitm(char **c);
void			envm(char **c, int fd, int false, t_pipeline *var);
void			pwd(char **c, int fd, int false, t_pipeline *var);
void			echo(char **c, int fd, int false, t_pipeline *var);
void			cd(char **c, int false);
int				serch_on_env(char *c, int *error);
void			copie_table(char **cp);
void			free_table(char **c);
int				errorin_args(char *c, int error, int i);
int				replace(int i, char *c);
int				input_error(char *c);
int				args_error(char *c, int false, char *name);
void			free_tree(t_template *lst);
void			signal_callback_handler(int sig);
char			**creat_table(t_template *lst);
void			generate_rederaction(int type, t_template *lst, int *error);
void			fd_of_redir(t_template	*tmp, int *fd,
					int *error);
int				agr_in_next_token(t_lexer *lexer);
void			qeuat_detect(char *quat, int *type, char c, int *ii);
void			string_join(t_lexer *lexer, char **text, int *type);
void			if_type_def_left_redirection_and_dr(int type,
					t_derections	*temp, int *error);
char			*redir_type(t_template *lst);
int				ambiguous_redir(int *fd, char *file);
int				qaut_detect_and_break_in_other(t_lexer *lexer, char **text,
					int *type, char quat);
void			print_error_of_rtext(void);
void			print_error_of_generate_rederaction(t_derections *temp,
					int *error);
int				lop_onarg(char *c);
void			redir_or_pipe(int pipe_exist, int fd, t_pipeline *var);
#endif
