NAME = minishell

SRC_P = lexer.c lexer_tool.c\

CC = @gcc 

CFLAGS = -lreadline -Wall -Wextra -Werror -g -fsanitize=address


LIBFT = libft/libft.a

RM = @rm -f

all:		$(NAME)

$(NAME):
			@cd libft && make && make bonus && cd ..
			$(CC) $(CFLAGS) $(LIBFT) $(SRC_P) -o $(NAME)
			@echo "\033[0;92m®MINISHELL CREATED 📟"

clean:
			@cd libft && make clean && cd ..

fclean: 	
			@cd libft && make fclean && cd ..
			$(RM) $(NAME)
			@echo "\033[0;31mMINISHELL DELETED 🗑"
re:			fclean all

#  github bigin
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
