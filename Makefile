# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/29 21:04:13 by hyeonski          #+#    #+#              #
#    Updated: 2020/12/29 21:04:15 by hyeonski         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = cub3d
TARGET_B = cub3d_bonus
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
	   ./srcs/valid_map.c \
	   ./srcs/bmp.c \
	   ./srcs/key_handle.c \
	   ./srcs/player_move.c \
	   ./srcs/dda.c \
	   ./srcs/draw_floor_ceil.c \
	   ./srcs/draw_sprite_utils.c \
	   ./srcs/draw_sprite.c \
	   ./srcs/draw_wall.c \
	   ./srcs/valid_key.c \
	   ./srcs/valid_map_utils.c \
	   ./srcs/arr_utils.c \
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
		 ./srcs_bonus/parse_value.c \
		 ./srcs_bonus/set_map.c \
		 ./srcs_bonus/set_player.c \
		 ./srcs_bonus/set_cub.c \
		 ./srcs_bonus/error.c \
		 ./srcs_bonus/utils.c \
		 ./srcs_bonus/validation.c \
		 ./srcs_bonus/valid_map.c \
		 ./srcs_bonus/bmp.c \
		 ./srcs_bonus/key_handle.c \
		 ./srcs_bonus/player_move.c \
		 ./srcs_bonus/dda.c \
		 ./srcs_bonus/draw_floor_ceil.c \
		 ./srcs_bonus/draw_sprite_utils.c \
		 ./srcs_bonus/draw_sprite.c \
		 ./srcs_bonus/draw_wall.c \
		 ./srcs_bonus/valid_key.c \
		 ./srcs_bonus/valid_map_utils.c \
		 ./srcs_bonus/arr_utils.c \
		 ./srcs_bonus/main.c

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(LIBS) -o $@ $^

bonus : $(TARGET_B)

$(TARGET_B) : $(OBJS_B)
	$(CC) $(CFLAGS) $(LFLAGS) $(LIBS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean :
	$(RM) $(OBJS) $(OBJS_B)

fclean : clean
	$(RM) $(TARGET) $(TARGET_B)

re : fclean all
