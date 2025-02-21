NAME = cub

CFLAGS = -Wall -Wextra -Werror -I/Users/$(USER)/Desktop/CUB3D-42/MLX42/include

SRCS = cub.c get_next_line.c get_next_line_utils.c

MLX = /Users/$(USER)/Desktop/CUB3D-42/MLX42/build/libmlx42.a -ldl -lglfw -L/goinfre/yobourai/homebrew/opt/glfw/lib
INCLUDE = cub.h

OBJS = $(SRCS:.c=.o)

CC = gcc

all: $(NAME) $(INCLUDE)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
