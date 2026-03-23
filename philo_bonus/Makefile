SRCS_DIR=srcs/
INCLUDES_DIR=includes/
OBJS_DIR=objs/
SRCS=fork_bonus.c init_bonus.c philo_bonus.c state_bonus.c time_bonus.c \
	tools_bonus.c
OBJECTS=$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
CFLAGS=-Werror -Wall -Wextra -g
CC=gcc
NAME=philo_bonus

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $^
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
