NAME = cub3D
CFLAGS = -Wall -Wextra -Werror
SRC_NAME = check_grid.c \
		ck_form.c \
		config_grid.c \
		config.c \
		error.c \
		free.c \
		init.c \
		main.c \
		player.c \
		raycasting.c \
		render.c \
		run_mlx.c \
		screen_shot.c \
		screen.c \
		set_cub3d.c \
		sp_screen.c \
		sprite.c \
		texture.c
SRC_PATH = ./srcs
SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = ./obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

INC_LINK = -I./include

UNAME := $(shell uname)
MLX_LNK	= -lmlx -framework Opengl -framework APPKIT
FT_LINK = -L./lib/libft -lft

all : $(NAME)

$(NAME): $(OBJ) libft
	gcc $(CFLAGS) $(OBJ) $(INC_LINK) $(MLX_LNK) $(FT_LINK) -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@gcc $(CFLAGS) $(INC_LINK) -o $@ -c $<

# libft compile
libft :
	@$(MAKE) -C ./lib/libft all

clean :
	@$(MAKE) -C ./lib/libft clean
	@rm -rf ./obj

fclean :
	@$(MAKE) -C ./lib/libft fclean
	@rm -rf ./obj $(NAME) screenshot.bmp

re : fclean all

norme:
	@norminette $(SRC) $(LIB) $(INC)

.PHONY: all clean fclean re norm
