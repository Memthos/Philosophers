CFLAGS=-Werror -Wall -Wextra -g
CC=cc
NAME=philo

all: $(NAME)

$(NAME):

re: clean all

clean:

fclean: clean

.PHONY: all clean fclean re