NAME = minishell
LIBNAME = libmini.a
CC = gcc
LDFLAGS = -lreadline -lncurses
CFLAGS = -Wall -Wextra -Werror

# Main files
files = error_checks/error_msg parcing/ops parcing/parcer parcing/token main parcing/tokenizer parcing/variables utils/helper_funcs/helps\

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