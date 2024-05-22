NAME	:=	minishell
CFLAGS	:=	-Wall -Wextra -Werror -g3

CRST	:=	"\033[0m"
CGRN	:=	"\033[32m"

DIR_INCL	:=	include
DIR_OBJS	:=	objects
DIR_LIBS	:=	library
DIR_L_FT	:=	libft
DIR_SRCS	:=	source
DIR_MAIN	:=	main
DIR_LINK	:=	linked_list
DIR_ENVP	:=	envp
DIR_EXPD	:=	expander
DIR_LEXR	:=	lexer
DIR_TYPE	:=	type_assignment
DIR_UTLS	:=	utils
DIR_PARS	:=	parser
DIR_EXEC	:=	execution

MAIN 	:=	$(DIR_MAIN)/main					\
			$(DIR_MAIN)/program					\
			$(DIR_MAIN)/signals					\

LINK	:=	$(DIR_LINK)/free					\
			$(DIR_LINK)/linked_list				\

ENVP	:=	$(DIR_ENVP)/create_env_list			\
			$(DIR_ENVP)/update_env_list			\

EXPD	:=	$(DIR_EXPD)/expand_part1			\
			$(DIR_EXPD)/expand_part2			\

LEXR	:=	$(DIR_LEXR)/lexer					\
			$(DIR_LEXR)/process_word			\
			$(DIR_LEXR)/process_delimiter		\

TYPE	:=	$(DIR_PARS)/$(DIR_TYPE)/files					\
			$(DIR_PARS)/$(DIR_TYPE)/path					\
			$(DIR_PARS)/$(DIR_TYPE)/builtins				\
			$(DIR_PARS)/$(DIR_TYPE)/type_assignment			\
			$(DIR_PARS)/$(DIR_TYPE)/commands_and_arguments	\

PARS	:=	$(DIR_PARS)/parser					\
			$(DIR_PARS)/quotes					\
			$(DIR_PARS)/pipe_error				\
			$(DIR_PARS)/syntax_error			\
			$(DIR_PARS)/remove_quotes			\
			$(DIR_PARS)/redirect_error			\

EXEC	:=	$(DIR_EXEC)/execution				\
			$(DIR_EXEC)/split_path_var			\
			$(DIR_EXEC)/exec_utils				\
			$(DIR_EXEC)/command_table			\
			$(DIR_EXEC)/find_executable			\
			$(DIR_EXEC)/handle_redirect			\
			$(DIR_EXEC)/env_list_to_str_array	\
			$(DIR_EXEC)/execute_simple_command	\
			$(DIR_EXEC)/create_absolute_path	\

UTLS	:=	$(DIR_UTLS)/utils_ft				\
			$(DIR_UTLS)/utils_quote				\
			$(DIR_UTLS)/utils_tokens			\
			$(DIR_UTLS)/utils_redirect			\
			$(DIR_UTLS)/utils_delimiter			\

SRCS	:=	${MAIN}								\
			${LINK}								\
			${ENVP}								\
			${EXPD}								\
			${LEXR}								\
			${TYPE}								\
			$(PARS)								\
			$(EXEC)								\
			$(UTLS)								\

L_FT	:=	./$(DIR_LIBS)/libft
LIBS	:=	-lreadline $(L_FT)/libft.a
INCS	:=	-I ./$(DIR_INCL) -I $(L_FT)/$(DIR_INCL)

OBJS	:=	$(addprefix $(DIR_OBJS)/,$(addsuffix .o,$(SRCS)))

all: make_libft $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c | $(DIR_OBJS)
	$(CC) $(CFLAGS) -o $@ -c $<
	printf $(CGRN)"Compiling: "$(CRST)"$<\n"

$(DIR_OBJS):
	mkdir -p $@
	mkdir -p $@/$(DIR_MAIN)
	mkdir -p $@/$(DIR_LINK)
	mkdir -p $@/$(DIR_ENVP)
	mkdir -p $@/$(DIR_EXPD)
	mkdir -p $@/$(DIR_LEXR)
	mkdir -p $@/$(DIR_PARS)
	mkdir -p $@/$(DIR_PARS)/$(DIR_TYPE)
	mkdir -p $@/$(DIR_EXEC)
	mkdir -p $@/$(DIR_UTLS)

$(NAME): make_libft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCS) -o $(NAME)

clean:
	$(MAKE) -C $(L_FT) clean
	rm -rf $(DIR_OBJS)

fclean: clean
	$(MAKE) -C $(L_FT) fclean
	rm -rf $(NAME)

re: fclean all

make_libft:
	$(MAKE) -C $(L_FT)

valgrind: re
	valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--suppressions=suppression.supp \
	./$(NAME)

.PHONY:	all clean fclean re make_libft valgrind

.SILENT:
