NAME = minishell
LIBNAME = libmini.a
CC = gcc
LDFLAGS = -lreadline -lncurses
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Main files
files = parcing/parcer parcing/token main\
		error_checks/pipe_err_check error_checks/redirection_err\
		error_checks/side_functions wild_card/expand_wild\
		parcing/tokenizer var_expansion/arg_replace\
		var_expansion/expanding var_expansion/misc\
		var_expansion/support var_expansion/variables\
		utils/helper_funcs/helps quotes/quote_stripping\
		wild_card/file_read var_expansion/norm\

CFILES = $(files:%=%.c)
OBJS = $(files:%=%.o)

LIBFT_DIR = utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBNAME): $(OBJS)
	ar crs $@ $(OBJS)

%.o: %.c includes.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LIBNAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re