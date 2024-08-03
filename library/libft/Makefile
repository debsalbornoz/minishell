NAME	:= libft.a

CFLAGS	:= -Wall -Wextra -Werror -g

FILES	:=					\
	ft_isalpha				\
	ft_isdigit				\
	ft_isalnum				\
	ft_isascii				\
	ft_isprint				\
	ft_strlen				\
	ft_memset				\
	ft_bzero				\
	ft_memcpy				\
	ft_memmove				\
	ft_strlcpy				\
	ft_strlcat				\
	ft_toupper				\
	ft_tolower				\
	ft_strchr				\
	ft_strrchr				\
	ft_strncmp				\
	ft_memchr				\
	ft_memcmp				\
	ft_strnstr				\
	ft_atoi					\
	ft_calloc				\
	ft_strdup				\
	ft_substr				\
	ft_strjoin				\
	ft_strtrim				\
	ft_split				\
	ft_itoa					\
	ft_strmapi				\
	ft_striteri				\
	ft_putchar_fd			\
	ft_putstr_fd			\
	ft_putendl_fd			\
	ft_putnbr_fd			\
	ft_print_decimal		\
	ft_print_hexadecimal	\
	ft_print_pointer		\
	ft_printf				\
	ft_putchar				\
	ft_putstr				\
	ft_unsigned				\
	get_next_line

SRC	:=	$(addprefix source/, $(addsuffix .c, $(FILES)))
OBJ	:=	$(addprefix objects/, $(addsuffix .o, $(FILES)))

all: $(NAME)

objects/%.o: source/%.c | objects
	$(CC) $(CFLAGS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

objects:
	mkdir -p objects

clean:
	rm -rf objects

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all objects clean fclean re objects

.SILENT:
