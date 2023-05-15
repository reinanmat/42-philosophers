NAME = philo_bonus

SRCS_PATH_BONUS = ./sources_bonus/
OBJS_PATH_BONUS = ./objects_bonus/

FILES_BONUS = main_bonus \
			  get_time_bonus \
			  child_processes_bonus \
			  print_action_bonus \
			  routine_bonus \
			  init_struct_bonus \
			  check_args_bonus \
			  utils_bonus

SRCS_BONUS = $(addprefix $(SRCS_PATH_BONUS), $(addsuffix .c, $(FILES_BONUS)))
OBJS_BONUS = $(addprefix $(OBJS_PATH_BONUS), $(addsuffix .o, $(FILES_BONUS)))

INCLUDES_BONUS = ./includes_bonus/
CFLAGS = -Wall -Wextra -Werror -g3 

all: $(NAME)

$(NAME): $(OBJS_BONUS)
	cc $(CFLAGS) -o $(NAME) $(OBJS_BONUS) -pthread

$(OBJS_PATH_BONUS)%.o: $(SRCS_PATH_BONUS)%.c | $(OBJS_PATH_BONUS)
	cc $(CFLAGS) -I $(INCLUDES_BONUS) -c $< -o $@

$(OBJS_PATH_BONUS):
	mkdir -p $(OBJS_PATH_BONUS)

bonus: all

clean:
	rm -rf $(OBJS_PATH_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
