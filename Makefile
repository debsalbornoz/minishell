CFLAGS = -g3 -Wall -Wextra -Werror
SRCS = minishell.c utils.c lexer.c
OBJ = $(SRCS:.c=.o)
NAME = minishell
LIBFT_DIR = ./libft

all: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJ)
	cc -g3 -Wall -Wextra -Werror minishell.o utils.o lexer.o -L./libft -lft -o minishell -lreadline -lncurses -ltermcap

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: all
	valgrind --suppressions=suppression.supp ./$(NAME) # Corrigido para usar $(NAME) em vez de ./minishell

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ) $(NAME)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) libft.a

re: fclean all