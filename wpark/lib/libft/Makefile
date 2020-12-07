NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -I$(INC_PATH) -c

SRC_PATH = .
OBJ_PATH = .
INC_PATH = ../../include

SRC_NAME = ft_atoi.c \
		ft_isdigit.c \
		ft_itoa.c \
		ft_putstr_fd.c \
		ft_strcmp.c \
		ft_strdup.c \
		ft_strfree.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strsub.c \
		ft_strlast.c \
		get_next_line.c

OBJ_NAME = $(SRC:.c=.o)
INC_NAME = libft.h

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))

all : $(NAME)

$(NAME) : $(OBJ)
		@ar rcs $(NAME) $(OBJ)
		@ranlib $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean : 
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

norme:
	@norminette $(SRC) $(LIB) $(INC)

.PHONY: all clean fclean re norm