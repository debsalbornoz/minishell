NAME		:=		\
	minishell

CFLAGS		:=		\
	-Wall -Wextra -Werror -g

LIBFT		:=		\
	./library/libft

LFLAGS		:=		\
	valgrind --leak-check=full

HEADERS		:=		\
	-I ./include -I $(LIBFT)/include

LIBS		:=		\
	-lreadline $(LIBFT)/libft.a

F_SOURCE	:=		\
	main			\

F_MAIN		:=		\
	program			\
	linked_list		\
	env_list

F_LEXER		:=		\
	tokenization	\
	redirect		\
	form_word		\
	type_assignment \
	commands		\
	files

F_UTILS		:=		\
	utils_quote		\
	utils_delimiter	\
	utils_redirect	\
	utils_tokens

O_SOURCE	:=		\
	$(addprefix objects/, $(addsuffix .o, $(F_SOURCE)))

O_MAIN		:=		\
	$(addprefix objects/main/, $(addsuffix .o, $(F_MAIN)))

O_LEXER		:=		\
	$(addprefix objects/lexer/, $(addsuffix .o, $(F_LEXER)))

O_UTILS		:=		\
	$(addprefix objects/utils/, $(addsuffix .o, $(F_UTILS)))

all: make_libft $(NAME)

make_libft:
	$(MAKE) -C $(LIBFT)

objects/%.o: source/%.c | objects
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

objects/main/%.o: source/main/%.c | objects/main
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

objects/lexer/%.o: source/lexer/%.c | objects/lexer
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

objects/utils/%.o: source/utils/%.c | objects/utils
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(O_SOURCE) $(O_MAIN) $(O_LEXER) $(O_UTILS)
	$(CC) $(O_SOURCE) $(O_MAIN) $(O_LEXER) $(O_UTILS) $(LIBS) $(HEADERS) -o $(NAME)

objects:
	mkdir -p objects

objects/main:
	mkdir -p objects/main

objects/lexer:
	mkdir -p objects/lexer

objects/utils:
	mkdir -p objects/utils

play: re
	clear && ./minishell

valgrind: re
	valgrind --suppressions=suppression.supp ./$(NAME)

leak: re
	clear && $(LFLAGS) ./minishell

clean:
	$(MAKE) -C $(LIBFT) clean
	clear && rm -rf objects

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY:
	all				\
	make_libft:		\
	clean			\
	fclean			\
	re				\
	play			\
	leak			\
	objects			\
	objects/main	\
	objects/lexer	\
	objects/utils

.SILENT:
