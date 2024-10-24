NAME = philo
NAME_BONUS = philo_bonus

src = philosophers/1_check_agv.c philosophers/2_set_data.c \
	philosophers/3_set_philo.c philosophers/4_simulate.c \
	philosophers/5_doing.c philosophers/6_take_forks.c \
	philosophers/7_printing.c philosophers/main.c

src_bonus = bonus/1_check_agv.c bonus/2_set_data.c \
	bonus/3_ini_sems.c bonus/4_simulate.c \
	bonus/5_doing.c bonus/main.c

headers = philosophers/philo.h
headers_bonus = bonus/philo.h

obj = $(src:.c=.o)
obj_bonus = $(src_bonus:.c=.o)

flags = -Wall -Werror -Wextra

cc = cc #-pthread -fsanitize=address -g

all: $(NAME)
bonus: $(NAME_BONUS)

$(NAME): $(src) $(obj) $(headers)
	$(cc) $(flags) $(src) -o $(NAME)

$(NAME_BONUS): $(src_bonus) $(obj_bonus) $(headers_bonus)
	$(cc) $(flags) $(src_bonus) -o $(NAME_BONUS)

%.o: %.c $(headers)
	$(cc) $(flags) -c $< -o $@

clean:
	rm -rf $(obj) $(obj_bonus)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all bonus

.PHONY: all clean fclean re
