TARGET = cub3D
INCLUDES = -I ./includes -I /usr/local/include
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L /usr/local/lib
LIBS = -lmlx -framework OpenGL -framework AppKit
CC = gcc
RM = rm -f

SRCS = lodev.c	\
	   map_parser.c	\
	   libft/ft_atoi.c	\
	   libft/get_next_line.c	\
	   get_next_line/get_next_line.c	\
	   get_next_line/get_next_line_utils.c	\

OBJS = $(SRCS:.c=.o)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(LIBS) -o $@ $^

bonus : all

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(TARGET)

re : fclean all
