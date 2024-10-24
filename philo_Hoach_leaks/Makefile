NAME = philo

src = philosophers/1_check_agv.c philosophers/2_agc_data.c \
	philosophers/3_set_philo.c philosophers/4_helpers.c philosophers/main.c

headers = philosophers/philo.h

obj = $(src:.c=.o)

flags = -Wall -Werror -Wextra

cc = gcc -pthread -fsanitize=address -g

all: $(NAME)

$(NAME): $(src) $(obj) $(headers)
	$(cc) $(flags) $(src) -o $(NAME)

%.o: %.c
	$(cc) $(flags) -c $< -o $@

clean:
	rm -rf $(obj)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
