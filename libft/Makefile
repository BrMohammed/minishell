NAME = libft.a

CC = @gcc -c

FLAGS = -Wall -Wextra -Werror

AR = ar rc

RM = rm -f

FILES = ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c

FILES_BONUS = ft_lstnew_bonus.c\
			  ft_lstadd_front_bonus.c\
			  ft_lstsize_bonus.c\
			  ft_lstlast_bonus.c\
			  ft_lstadd_back_bonus.c\
			  ft_lstdelone_bonus.c\
			  ft_lstclear_bonus.c\
			  ft_lstiter_bonus.c\
			  ft_lstmap_bonus.c


objets = 	$(FILES:.c=.o)
objets_b =	$(FILES_BONUS:.c=.o)

all :$(NAME)


$(NAME):	$(objets)
			@$(AR) $(NAME) $(objets)
			@echo "\033[0;92m{LIBFT} PROJECT FILE CREATED ✅"

$(objets):$(FILES)
	$(CC) $(FLAGS) $(FILES)
	
clean :
			@$(RM) $(objets) $(objets_b)
			@echo "\033[0;93m{LIBFT} OBJECTS DELETED ❌"

fclean :	clean
			@$(RM) $(NAME)
			@echo "\033[0;93m{LIBFT} PROJECT File DELETED ❌"

re :		fclean all

bonus:		$(objets_b)

$(objets_b):	$(FILES_BONUS)
				$(CC)  $(FLAGS) $(FILES_BONUS)
				@$(AR) $(NAME) $(objets_b)
				@echo "\033[0;92m{LIBFT} BONUS CREATED ✅"


rebonus :	fclean bonus
