NAME = philo

SOURCES = errors.c philo.c utilse.c initialasing.c monitor.c \
		taking_forks.c routine.c check_print.c initiakizing2.c
OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

$(NAME_BONUS): $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) $(OBJECTS_BONUS) -o $(NAME_BONUS)

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJECTS)
