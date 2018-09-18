
NAME = RTv1

LIBFT_NAME = libft.a

LIBFT_PATH = libft/$(LIBFT_NAME)

LIBMLX_NAME = libmlx.a

LIBMLX_PATH = minilibx/$(LIBMLX_NAME)

LIBPNT_NAME = libpnt.a

LIBPNT_PATH = libpnt/$(LIBPNT_NAME)

SRCS = src/*.c

HEAD = rtv1.h

CFLAGS = -Wall -Wextra -Werror -pthread

# MacOSX flags

FLAGS = -lmlx -framework OpenGL -framework AppKit

# UNIX / Linux flags

# FLAGS = -lmlx -lXext -lX11

CC = gcc

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re

all: $(NAME)

$(NAME):
	@$(MAKE) -C libft
	@$(MAKE) -C minilibx
	@$(MAKE) -C libpnt
	@$(CC) $(CFLAGS) $(SRCS) -Ilibft -Iminilibx -Ilibpnt -o $(NAME) \
		$(LIBFT_PATH) $(LIBMLX_PATH) $(LIBPNT_PATH) $(FLAGS)

clean:
	@/bin/rm -f src/*.o
	@$(MAKE) clean -C libft
	@$(MAKE) clean -C minilibx

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) fclean -C libft
	@/bin/rm -f $(LIBMLX_PATH)

re: fclean all
