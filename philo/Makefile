NAME = philo

SRCS_PATH = ./sources/
OBJS_PATH = ./objects/

FILES = main \
		check_args \
		forks \
		init_struct \
		print_action \
		routine \
		monitoring \
		get_time \
		utils

SRCS = $(addprefix $(SRCS_PATH), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_PATH), $(addsuffix .o, $(FILES)))

INCLUDES = ./includes/
CFLAGS = -Wall -Wextra -Werror -g3 

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS) -pthread

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c | $(OBJS_PATH)
	cc $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

clean:
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
