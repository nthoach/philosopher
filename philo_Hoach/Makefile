NAME = philo

src = philo/philo.c philo/lib.c
hd = philo/philo.h

obj = $(src:.c=.o)

flags = -Wall -Werror -Wextra

cc = cc

all: $(NAME)

$(NAME): $(src) $(obj) $(hd)
	$(cc) $(flags) $(src) - o $(NAME)

%.o: %.c
	$(cc) $(flags) -c $< -o $@

clean:
	rm -rf $(obj)

fclean: clean
	rm -rf $(NAME)

re: fclean all