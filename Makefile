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
	expand_part1	\
	expand_part2	\
	program			\
	linked_list		\
	free			\
	signals

F_ENVP		:=				\
	create_env_list			\
	update_env_list			\

F_LEXER		:=				\
	lexer					\
	process_delimiter		\
	process_word			\

F_TYPE	:=			\
	type_assignment \
	commands		\
	arguments		\
	builtins		\
	files			\
	path

F_UTILS		:=		\
	utils_quote		\
	utils_delimiter	\
	utils_redirect	\
	utils_tokens	\
	utils_ft

F_PARSER	:=		\
	pipe_error		\
	redirect_error	\
	syntax_error	\
	parser			\
	remove_quotes	\
	split_path			\
	lexycal_analysis	\
		quotes			\

F_EXECUTION		:=	\
	execute_simple_command \
	execution		\
	command_table	\
	env_list_to_str_array	\
	save_path		\
	handle_output_redirect \
	handle_redirect

O_SOURCE	:=		\
	$(addprefix objects/, $(addsuffix .o, $(F_SOURCE)))

O_MAIN		:=		\
	$(addprefix objects/main/, $(addsuffix .o, $(F_MAIN)))

O_ENVP		:=		\
	$(addprefix objects/envp/, $(addsuffix .o, $(F_ENVP)))

O_LEXER		:=		\
	$(addprefix objects/lexer/, $(addsuffix .o, $(F_LEXER)))

O_TYPE		:=		\
	$(addprefix objects/parser/type/, $(addsuffix .o, $(F_TYPE)))

O_UTILS		:=		\
	$(addprefix objects/utils/, $(addsuffix .o, $(F_UTILS)))

O_PARSER	:=		\
	$(addprefix objects/parser/, $(addsuffix .o, $(F_PARSER)))

O_EXECUTION	:=		\
	$(addprefix objects/execution/, $(addsuffix .o, $(F_EXECUTION)))

all: make_libft $(NAME)

make_libft:
	$(MAKE) -C $(LIBFT)

objects/%.o: source/%.c | objects
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

objects/main/%.o: source/main/%.c | objects/main
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

objects/envp/%.o: source/envp/%.c | objects/envp
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

objects/lexer/%.o: source/lexer/%.c | objects/lexer
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

objects/parser/type/%.o: source/parser/type/%.c | objects/parser/type
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

objects/utils/%.o: source/utils/%.c | objects/utils
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

objects/parser/%.o: source/parser/%.c | objects/parser
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"
objects/execution/%.o: source/execution/%.c | objects/execution
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(O_SOURCE) $(O_MAIN) $(O_ENVP) $(O_LEXER) $(O_TYPE) $(O_UTILS) $(O_PARSER) $(O_EXECUTION)
	$(CC) $(O_SOURCE) $(O_MAIN) $(O_ENVP) $(O_LEXER) $(O_TYPE) $(O_UTILS) $(O_PARSER) $(O_EXECUTION) $(LIBS) $(HEADERS) -o $(NAME)

objects:
	mkdir -p objects

objects/main:
	mkdir -p objects/main

objects/envp:
	mkdir -p objects/envp

objects/lexer:
	mkdir -p objects/lexer

objects/parser/type:
	mkdir -p objects/parser/type

objects/utils:
	mkdir -p objects/utils

objects/parser:
	mkdir -p objects/parser

objects/execution:
	mkdir -p objects/execution
play: re
	clear && ./minishell

valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=suppression.supp ./$(NAME)

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
	all					\
	make_libft:			\
	clean				\
	fclean				\
	re					\
	play				\
	leak				\
	objects				\
	objects/main		\
	objects/envp		\
	objects/lexer		\
	objects/parser/type	\
	objects/utils		\
	objects/parser		\
	objects/execution

.SILENT:
