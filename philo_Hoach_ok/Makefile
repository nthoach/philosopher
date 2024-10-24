NAME = philo
NAME_BONUS = philo_bonus

src = philo_src/1_check_agv.c philo_src/2_set_data.c \
	philo_src/3_set_philo.c philo_src/4_simulate.c \
	philo_src/5_doing.c philo_src/6_take_forks.c \
	philo_src/7_printing.c philo_src/main.c

src_bonus = philo_bonus_src/1_check_agv.c philo_bonus_src/2_set_data.c \
	philo_bonus_src/3_ini_sems.c philo_bonus_src/4_simulate.c \
	philo_bonus_src/5_doing.c philo_bonus_src/main.c

headers = philo_src/philo.h
headers_bonus = philo_bonus_src/philo.h

obj = $(src:.c=.o)
obj_bonus = $(src_bonus:.c=.o)

flags = -Wall -Werror -Wextra

cc = cc -pthread #-fsanitize=address -g

all: $(NAME)
bonus: $(NAME_BONUS)

$(NAME): $(src) $(obj) $(headers)
	$(cc) $(flags) $(src) -o $(NAME)

$(NAME_BONUS): $(src_bonus) $(obj_bonus) $(headers_bonus)
	$(cc) $(flags) $(src_bonus) -o $(NAME_BONUS)

%.o: %.c $(headers)
	$(cc) $(flags) -c $< -o $@

clean:
	rm -f $(obj) $(obj_bonus)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all bonus

.PHONY: all clean fclean re
