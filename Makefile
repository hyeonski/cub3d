TARGET = cub3d
INCLUDES = -I ./includes
CFLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror
LFLAGS = -L ./mlx
LIBS = -lmlx -framework OpenGL -framework AppKit
CC = gcc
RM = rm -f

SRCS = ./libft/ft_memset.c \
	   ./libft/ft_bzero.c \
	   ./libft/ft_memcpy.c \
	   ./libft/ft_memccpy.c \
	   ./libft/ft_memmove.c \
	   ./libft/ft_memchr.c \
	   ./libft/ft_memcmp.c \
	   ./libft/ft_strcmp.c \
	   ./libft/ft_strlen.c \
	   ./libft/ft_atoi.c \
	   ./libft/ft_calloc.c \
	   ./libft/ft_strdup.c \
	   ./libft/ft_strjoin.c \
	   ./libft/ft_split.c \
	   ./libft/ft_strchr.c \
	   ./libft/ft_substr.c \
	   ./libft/ft_putchar_fd.c \
	   ./libft/ft_putstr_fd.c \
	   ./libft/ft_putendl_fd.c \
	   ./libft/ft_lstsort.c \
	   ./libft/ft_lstforeach.c \
	   ./libft/ft_lstpush_back.c \
	   ./libft/ft_create_elem.c \
	   ./libft/ft_lstlast.c \
	   ./get_next_line/get_next_line.c \
	   ./srcs/parse_value.c \
	   ./srcs/set_map.c \
	   ./srcs/set_player.c \
	   ./srcs/set_cub.c \
	   ./srcs/error.c \
	   ./srcs/utils.c \
	   ./srcs/validation.c \
	   ./srcs/key_handle.c \
	   ./srcs/main.c

SRCS_B = ./libft/ft_memset.c \
		 ./libft/ft_bzero.c \
		 ./libft/ft_memcpy.c \
		 ./libft/ft_memccpy.c \
		 ./libft/ft_memmove.c \
		 ./libft/ft_memchr.c \
		 ./libft/ft_memcmp.c \
		 ./libft/ft_strcmp.c \
		 ./libft/ft_strlen.c \
		 ./libft/ft_atoi.c \
		 ./libft/ft_calloc.c \
		 ./libft/ft_strdup.c \
		 ./libft/ft_strjoin.c \
		 ./libft/ft_split.c \
		 ./libft/ft_strchr.c \
		 ./libft/ft_substr.c \
		 ./libft/ft_putchar_fd.c \
		 ./libft/ft_putstr_fd.c \
		 ./libft/ft_putendl_fd.c \
		 ./libft/ft_lstsort.c \
		 ./libft/ft_lstforeach.c \
		 ./libft/ft_lstpush_back.c \
		 ./libft/ft_create_elem.c \
		 ./libft/ft_lstlast.c \
		 ./get_next_line/get_next_line.c \
		 ./srcs/parse_value.c \
		 ./srcs/set_map.c \
		 ./srcs/set_player.c \
		 ./srcs/set_cub.c \
		 ./srcs/error.c \
		 ./srcs/utils.c \
		 ./srcs/validation.c \
		 ./srcs/key_handle.c \
		 ./srcs/main.c \
		 ./srcs/draw_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(LIBS) -o $@ $^

bonus : $(OBJS_B)
	$(CC) $(CFLAGS) $(LFLAGS) $(LIBS) -o $(TARGET) $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean :
	$(RM) $(OBJS) $(OBJS_B)

fclean : clean
	$(RM) $(TARGET)

re : fclean all
