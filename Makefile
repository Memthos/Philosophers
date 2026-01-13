SRCS_DIR=srcs/
INCLUDES_DIR = includes/
OBJS_DIR = objs/
SRCS=philo.c tools.c
OBJECTS=$(addprefix $(OBJS_DIR, $(SRCS.c=.o)))
CFLAGS=-Werror -Wall -Wextra -g
CC=cc
NAME=philo

all: $(NAME)

$(NAME): $(OBJS) -o $@ $^
	@$(CC) $(CFLAGS)
	@echo "Finished compiling philo"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -drf $(OBJS_DIR)
	@echo "Cleaned philo object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned philo"

re: clean all
	@echo "Recompiled philo"

.PHONY: all clean fclean re