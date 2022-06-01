NAME = minishell

SRC_P = lexer.c parser.c error.c struct_tool.c\
		path_finder.c execution.c  here_doc.c main.c execution_begin.c builtins/export.c\
		builtins/unset.c builtins/exit_env_pwd.c builtins/echo.c builtins/cd.c

CC = @gcc 

CFLAGS = -lreadline -Wall -Wextra -Werror -g #-fsanitize=address


LIBFT = libft/libft.a

RM = @rm -f

all:		$(NAME)

$(NAME):
			@make -C libft && make bonus -C libft
			$(CC) $(CFLAGS) $(LIBFT) $(SRC_P) -o $(NAME)
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
