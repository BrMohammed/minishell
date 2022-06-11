NAME = minishell

SRC_P = parsing/lexer.c parsing/parser.c parsing/error.c parsing/struct_tool.c\
		parsing/path_finder.c parsing/free_tree.c parsing/struct_tool01.c parsing/handling_data.c parsing/handling_data01.c\
		parsing/handling_data02.c \
		execution.c  here_doc.c main.c execution_begin.c\
		builtins/export.c builtins/export01.c builtins/unset.c builtins/exit_pwd.c builtins/echo.c builtins/cd.c\
		builtins/env.c 

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
