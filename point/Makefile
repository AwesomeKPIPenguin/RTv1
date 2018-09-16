NAME = libpoint.a

SRCS = $(wildcard *.c)

OBJ = $(SRCS:.c=.o)

HEAD = point.h

CFLAGS = -Wall -Wextra -Werror

FLAGS = -lm

CC = gcc

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

clean:
	@/bin/rm -f *.o

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
