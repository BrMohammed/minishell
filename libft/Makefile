NAME = libft.a

CC = @gcc

FLAGS = 

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


objets = $(FILES:.c=.o)
objets_b = $(FILES_BONUS:.c=.o)

# Colors
C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_GREEN = \033[1;32m
C_BLUE = \033[1;34m
C_L_BLUE = \033[1;34m
C_WHITE = \033[1;37m
C_RES = \033[0m

#  github bigin

ADD = git add .

read :=	@read -p "-> " enter \
		&& git commit -m $${enter}

PU = git push

#  Syntax


all :$(NAME)


$(NAME):$(objets)
	@$(AR) $(NAME) $(objets)
	@echo "\n\n${C_GREEN}              ---> $(NAME) created <---${C_RES}"

$(objets):$(FILES)
	$(flag)
	$(CC) -c $(FLAGS) $(FILES)
	
clean :
	@$(RM) $(objets) $(objets_b)
	@echo "${C_RED}                    ---> Object is Removed <---${C_RES}"

fclean : clean
	@$(RM) $(NAME)
	@echo "${C_RED}                    ---> $(NAME) is Removed <---${C_RES}"

re : fclean all

bonus: $(objets_b)

$(objets_b):$(FILES_BONUS)
	$(flagB)
	$(CC) -c $(FLAGS) $(FILES_BONUS)
	@$(AR) $(NAME) $(objets_b)
	@echo "\n\n${C_GREEN}              ---> $(NAME) with bonus created <---${C_RES}"


rebonus : fclean bonus

push :
	$(ADD)
	@echo "${C_GREEN}Add Commit Plz !!${C_RES}"
	$(read)
	$(PU)

flag := @echo  "\n${C_L_BLUE}         +                   *                   +          ${C_RES}"\
			"\n${C_L_BLUE} +  --         --------   -------    --------   --------   ${C_RES}"\
		    "\n${C_L_BLUE}   |  |       |__    __| |   --   \ |   _____| |__    __| *${C_RES}"\
			"\n${C_L_BLUE}   |  |  *       |  |    |  |__|  | |  |_____     |  |     ${C_RES}"\
			"\n${C_L_BLUE}   |  |          |  |    |       /  |   _____| +  |  |     ${C_RES}"\
			"\n${C_L_BLUE}   |  |      +   |  | *  |   --  |  |  |          |  |    *${C_RES}"\
			"\n${C_L_BLUE} * |  |_____   __|  |__  |  |__|  \ |  |          |  |     ${C_RES}"\
			"\n${C_L_BLUE}   |________| |________| |_______ / |__|     *    |__|     ${C_RES}"\
			"\n${C_L_BLUE}        +                                               *   ${C_RES}"\

flagB := @echo  "\n${C_L_BLUE}         +                   *                   +          ${C_RES}"\
			"\n${C_L_BLUE} +  --         --------   -------    --------   -------- ${C_RES} ${C_GREEN} -------    * ${C_RES}"\
		    "\n${C_L_BLUE}   |  |       |__    __| |   --   \ |   _____| |__    __|${C_RES} ${C_GREEN}|   --   \  ${C_RES}"\
			"\n${C_L_BLUE}   |  |  *       |  |    |  |__|  | |  |_____     |  |   ${C_RES} ${C_GREEN}|  |__|  | ${C_RES}"\
			"\n${C_L_BLUE}   |  |          |  |    |       /  |   _____| +  |  |   ${C_RES} ${C_GREEN}|       / ${C_RES}"\
			"\n${C_L_BLUE}   |  |      +   |  | *  |   --  |  |  |          |  |   ${C_RES} ${C_GREEN}|   --  |    *${C_RES}"\
			"\n${C_L_BLUE} * |  |_____   __|  |__  |  |__|  \ |  |          |  |   ${C_RES} ${C_GREEN}|  |__|  \ ${C_RES}"\
			"\n${C_L_BLUE}   |________| |________| |_______ / |__|     *    |__|   ${C_RES} ${C_GREEN}|_______ / ${C_RES}"\
			"\n${C_L_BLUE}        +                                               *${C_RES}"\
