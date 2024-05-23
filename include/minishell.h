/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:24 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/23 20:16:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../library/libft/include/libft.h"
# include <sys/wait.h>
# include <fcntl.h>

enum	e_type_signal
{
	FALSE,
	TRUE
};

enum	e_type_type
{
	DELIMITER	= 1000,
	REDIRECT	= 1100,
	INPUT		= 1110,
	HEREDOC		= 1120,
	OUTPUT		= 1130,
	APPEND		= 1140,
	PIPE		= 1200,
	WORD		= 2000,
	COMMAND		= 2100,
	EXECUTABLE	= 2110,
	BUILTIN		= 2120,
	ECHO		= 2121,
	CD			= 2122,
	PWD			= 2123,
	EXPORT		= 2124,
	UNSET		= 2125,
	ENV			= 2126,
	EXIT		= 2127,
	ARGUMENT	= 2200,
	FILES		= 2210,
	INPUT_FILE	= 2211,
	OUTPUT_FILE	= 2212,
	APPEND_FILE = 2213,
	FLAG		= 2220,
	HEREDOC_KEY	= 2230,
	PATH		= 3000,
	ERROR		= 9999,
};

typedef struct s_list	t_list;
typedef struct s_node	t_node;
union					u_data;
typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_exp	t_exp;
typedef struct s_exec	t_exec;

struct s_list
{
	t_node			*node;
	struct s_node	*head;
};

struct s_node
{
	union u_data	*data;
	struct s_node	*next;
};

union u_data
{
	t_token	*token;
	t_env	*env;
	t_exec	*execution;
};

struct s_env
{
	char			*name;
	char			*value;
};

struct s_token
{
	char			*value;
	int				type;
};

struct s_exp
{
	char			*input;
	char			*temp;
	char			sig_quote;
};

struct s_exec
{
	char			*path;
	char			**command_table;
	char			**envp;
	char			**redirects_and_files;
	int				input;
	int				output;
};

/* --- source/main --- */

// program.c
int		program(t_list *lst_env);

//signals.c
void	handle_sigint(int signal);
void	set_error(t_list *lst_env);
void	handle_signal(void);

/* --- source/linked_list --- */

// free.c
void	free_list(t_list *list, void (f)(t_list *));
void	free_lst_tokens(t_list *tokens);
void	free_lst_env(t_list *envp);
void	free_lst_exec(t_list *exec);
void	release_memory(t_list *tokens, t_list *exec, char *input);

// linked_list.c
t_list	*add_node(t_list *list);
t_list	*runs_on_list(t_list *list, t_node *(f)(t_node *));
int		count_nodes(t_list *lst);

/* --- source/envp/ --- */

//create_env_list.c
t_list	*data_env_addr(void);
t_list	*create_env_list(char **envp, t_list *env_lst);
char	*get_envp_name(char *envp);
char	*get_envp_value(char *envp);

//update_env_list.c
void	update_env_list(t_list *envp, char *name, char *value);

/* --- source/expander/ --- */

// expand_part1.c
char	*expand(t_list *lst_env, char *input);
char	*search_name(t_list *lst_env, t_exp *exp);

// expand_part2.c
char	*process_dollar(t_exp *exp);
char	*process_heredoc(t_exp *exp);
char	*process_doble_quote(t_list *lst_env, t_exp *exp);
char	*var_expand(t_exp *cur, t_env *var);
char	*var_is_null(char *value, char sig);

/* --- source/lexer/ --- */

//lexer.c
t_list	*lexer(t_list *tokens, char *input);
char	*trim_start_spaces(char *input);
char	process_quotes(char signal, char input);

// process_delimiter.c
int		process_delimiter(t_list *tokens, int signal, char *input, int i);
t_list	*process_redirect(t_list *tokens, char *input, int i);
t_list	*process_redirect_input(t_list *tokens, char *input, int i);
t_list	*process_redirect_output(t_list *tokens, char *input, int i);

// process_word.c
int		process_word(t_list *tokens, int signal, char *input, int i);
int		get_token_len(char *input, int signal);
int		is_empty_quotes(char signal, char *input);

/* --- source/parser/ --- */

//parser.c
int		parser(t_list *tokens, t_list	*envp, char *input);

//pipe_error.c
int		pipe_error(t_list	*tokens);
int		check_first_and_last_pipe(t_list	*tokens);
int		check_pipe_after_redirect(t_list	*tokens);

//quotes.c
int		is_closed(char *input, t_list *envp);
int		count_characters_inside_quotes(const char *str,
			int *i, char signal, int inside_quotes);
int		count_characters_outside_quotes(const char *str,
			int *i, int inside_quotes);
void	print_fatal_error(char *input, t_list *envp);

//redirect_error.c
int		find_redirect(int type);
int		redirect_error(t_list	*tokens);
int		redirect_at_end(t_list *tokens);

//remove_quotes.c
t_list	*remove_quotes(t_list *tokens);
t_node	*replace_str(t_node *node);
char	*unquote_str(char *str, char *temp, int i, int j);
int		find_new_len(const char *str, int len, int i, int counter);

//syntax_error.c
int		syntax_error(t_list *tokens, t_list	*lst_env, char *input);
int		redirect_error(t_list	*tokens);
int		dot_error(t_list	*tokens);

/* --- source/parser/type_assignment --- */

//builtins.c
t_node	*is_builtin(t_node *node);
int		identify_builtin(char *token, char *builtin, int token_len);
int		compare_quoted_strings(char *token, char *builtin);

//commands_and_arguments.c
t_node	*is_command_part1(t_node *head);
t_node	*is_command_part2(t_node *node);
t_node	*is_argument(t_node *node);
t_node	*is_command_part3(t_node *tokens);

// files.c
t_node	*is_file(t_node *node);
t_node	*is_heredoc_key(t_node *node);

//path.c
t_node	*is_path(t_node *node);

// type_assignment.c
t_list	*type_assignment(t_list *tokens);

/* --- source/utils/ --- */
// utils_delimiter.c
int		is_delimiter(char chr);
int		is_space(char chr);
int		is_pipe(char chr);
int		s_dollar(char chr);
int		is_redirect_or_pipe(int type);

// utils_ft.c
int		ft_strcmp(char	*str1, char *str2);
char	*ft_chrjoin(char *dest, char src);
char	*ft_rmchr(char *input, char *position);

// utils_quote.c
int		is_quote(char chr);
int		is_single_quote(char chr);
int		is_double_quote(char chr);

// utils_redirect.c
int		is_redirect(char chr);
int		is_redirect_input(char chr);
int		is_redirect_output(char chr);
int		is_heredoc(char chr, char next_chr);
int		is_append(char chr, char next_chr);

// utils_tokens.c
t_node	*print_tokens(t_node *node);

/* --- execution --- */

//command_table.c
void	create_command_table(t_list *tokens, t_list *exec);
char	**allocate_cmd_table(t_node *tokens);
void	create_simple_cmd_table(t_list *tokens, t_list *exec);
void	create_multi_cmd_table(t_list *tokens, t_list *exec);
char	**fill_command_table(t_node **tokens, char **command_table);

//create_absolute_path.c
char	*create_absolute_path(char **path_array, char **command_table,
			t_list *envp, t_node *exec);
char	*concatenate_path(char *path, char *command);

//env_list_to_str_array.c
char	**env_list_to_str_array(t_list *lst_env);
char	*build_env_var(char *s1, char *s2);

//exec_utils.c
int		find_file(int type);
int		is_file_redirect_or_pipe(int type);
void	free_and_update_lst(char **path_array, t_list	*envp);
void	free_matrix(char **matrix);

//execute_simple_command.c
int		is_simple_command(t_list *tokens);
int		execute_simple_command(t_list *exec, t_list *tokens);

//execution.c
t_list	*execute(t_list *tokens, t_list *exec, t_list *envp);
t_list	*allocate_lst_exec(t_list *tokens, t_list *exec, t_list *envp);
t_list	*create_lst_exec(t_list *tokens, t_list *exec, t_list *envp);

//handle_redirect.c
void	handle_redirect(t_node *tokens);
t_list	*open_file(t_list *tokens);
int		set_flag(char *redirect);
t_list	*remove_redirect_and_file(t_list *tokens);
void	close_fds(void);

//find_executable.c
void	fill_path_in_exec(t_list *tokens, t_list *exec, t_list *envp);
char	*validate_path(char **command_table, t_node *exec, t_list *envp);
int		is_absolute_path(char **command_table);
int		is_executable(t_node *exec, char *path);

//redirects_and_files.c
void	fill_redir_and_files(t_list *exec, t_list *tokens);
char	**allocate_matrix(t_node *tokens);
char	**get_redirects_and_files(t_node **tokens, char **redir_and_files);

//split_path_var.c
char	**split_path(t_list *envp);
int		count_paths(const char *value);
char	*return_value(t_list *envp, char *name);
char	*get_path(char *value, int i, int len, int j);
int		get_len(char *value);

#endif
