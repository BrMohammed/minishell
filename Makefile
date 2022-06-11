NAME = minishell

SRC_P = parsing/lexer.c parsing/parser.c parsing/error.c parsing/struct_tool.c\
		parsing/path_finder.c parsing/free_tree.c parsing/struct_tool01.c parsing/handling_data.c parsing/handling_data01.c\
		parsing/handling_data02.c \
		execution/execution.c  execution/here_doc.c execution/execution_begin.c execution/exucution_end.c\
		builtins/export.c builtins/export01.c builtins/unset.c builtins/exit_pwd.c builtins/echo.c builtins/cd.c\
		builtins/env.c\
		main.c

CC = @gcc 

RDLINE		:= -lreadline -L/goinfre/brmohamm/.brew/opt/readline/lib 

CFLAGS = -lreadline -Wall -Wextra -Werror -I/goinfre/brmohamm/.brew/opt/readline/include  #-fsanitize=address -g


LIBFT = libft/libft.a

RM = @rm -f

all:		$(NAME)

$(NAME):
			@make -C libft && make bonus -C libft
			$(CC) $(CFLAGS) $(RDLINE) $(LIBFT) $(SRC_P) -o $(NAME)
			@make clean -C libft
			@echo "®MINISHELL CREATED"


clean:
			@make clean -C libft

fclean: 	
			@make fclean -C libft
			$(RM) $(NAME)
			@echo "MINISHELL DELETED 🗑"
re:			fclean all

#  github bigin   # lsof -c minishell
# git pull --rebase origin main

#TODO:
#?	ls -la < adf  > ssaaa // dont create second file out if file one has error
#?	ls << aaaa > asdadaasdasdadas  //  ls > asdadaasdasdadas << asaa // dont create file if herdoc is interpted ctrl + c
#?	echo -n // segfault
#?	<<< this is syntax error dont show heredoc
#?	asdasd |  | asdasd // syntax error
#?	asdasd |  | asdasd | // syntax error too
#?	syntax error exit code 258
#?	|<s Dont show opening file errors after syntax parsing error

#!	unset path => ls // segfault after unsetting the PATH
#!	export dsaasd => unset dsadas // Leaks whene running any buildin cmd (cd / pwd) too echo is not leaking
#!	cd not working alone should gp to home or if home is not in env show home is not set show  cd ~ should go to home no matter if its unset
#!	cd .. or cd . // segfault // cd not working cd / segfault
#!	export d="    ls    -la   " => $d // segfault and the value is empty




ADD = git add .

read :=		@read -p "-> " enter \
			&& git commit -m $${enter}

PU =	git push

commit = git log --graph --oneline --decorate HEAD^..HEAD

t:	all
	./minishell

push :
	@$(commit)
	@$(ADD)
	$(read)
	$(PU)
