NAME = minishell

SRC_P = lexer.c parser.c error.c struct_tool.c\
		path_finder.c execution.c  here_doc.c main.c execution_begin.c builtins/export.c\
		builtins/unset.c builtins/exit_env.c

CC = @gcc 

CFLAGS = -lreadline -Wall -Wextra -Werror -g #-fsanitize=address


LIBFT = libft/libft.a

RM = @rm -f

all:		$(NAME)

$(NAME):
			@cd libft && make && make bonus && cd ..
			$(CC) $(CFLAGS) $(LIBFT) $(SRC_P) -o $(NAME)
			@cd libft && make clean && cd ..
			@echo "®MINISHELL CREATED"


clean:
			@cd libft && make clean && cd ..

fclean: 	
			@cd libft && make fclean && cd ..
			$(RM) $(NAME)
			@echo "MINISHELL DELETED 🗑"
re:			fclean all

#  github bigin   # lsof -c minishell
# git pull --rebase origin main

#</dev/random  cat | ls >lll

#< /dev/random cat | cat > out -w
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


# 	bash-3.2$ echo $h
# dddddd dddd 'gggg '

# bash-3.2$ echo "$h"
# dddddd       dddd 'gggg   '