/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:24 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/10 20:37:13 by dlamark-         ###   ########.fr       */
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
	VARIABLE	= 2300,
	ERROR		= 9999
};
extern int				g_signal;
typedef struct s_list	t_list;
typedef struct s_node	t_node;
union					u_data;
typedef struct s_token	t_token;
typedef struct s_env	t_env;

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
	t_exec	*execution
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
	char			next_chr;
};

struct s_exec
{
	char			*path;
	char			**command_table;
	int				simple;
	char			**envp;

};

/* --- source/main --- */

//init_env_addr.c

t_list	**data_env_addr(void);
void	init_data_env_addr(char **envp);

//signals.c

void	handle_sigint(int signal);
void	handle_signal(t_list *lst_env);
void	set_error(t_list *lst_env);

// env_list.c
t_list	*make_lst_env(char **envp);
char	*find_name(char *envp);
char	*find_value(char *envp);
t_node	*print_lst_env(t_node *node);


// expand_part1.c
char	*expand(t_list *lst_env, char *input);

// expand_part2.c
char	*var_expand(char *input, char *position, char *name, char *value);

// program.c
int		program(t_list *lst_env);

// linked_list.c
t_list	*add_node(t_list *list);
t_list	*runs_on_list(t_list *list, t_node *(f)(t_node *));

// free_list.c
void	free_list(t_list *list, void (f)(t_list *));
void	free_lst_tokens(t_list *tokens);
void	free_lst_env(t_list *env_list);

/* --- source/lexer/ --- */
// tokenization.c
t_list	*tokenization(t_list *lst_tokens, char *input);
char	*trim_start_spaces(char *input);
char	process_quotes(char signal, char input);
int		process_delimiter(t_list *lst_tokens, int signal, char *input, int i);

//lexycal_analysis.c

t_list	*lexical_analysis(char *input, t_list *lst_tokens);
int		check_input(char *input);
// redirect.c
t_list	*process_redirect(t_list *lst_tokens, char *input, int i);
t_list	*process_redirect_input(t_list *lst_tokens, char *input, int i);
t_list	*process_redirect_output(t_list *lst_tokens, char *input, int i);

// forme_word.c
int		form_word(t_list *lst_tokens, int signal, char *input, int i);
int		find_len(char *input, int signal);

// type assignment.C
t_list	*type_assignment(t_list *lst_tokens);

// commands.c
t_node	*is_command_part1(t_node *head);
t_node	*is_command_part2(t_node *node);

// arguments.c
t_node	*is_argument(t_node *node);

// builtins.c
int		ft_strlcmp(char *s1, char *s2, int len);
int		compare_quoted_strings(char *s1, char *s2);
t_node	*is_builtin(t_node *node);

// files.c
t_node	*is_file(t_node *node);
t_node	*is_heredoc_key(t_node *node);

// quotes.c
int		single_quotes_closed(char *input);
int		double_quotes_closed(char *input);
int		is_closed(char *input);

/* --- source/utils/ --- */
// utils_quote.c
int		is_quote(char chr);
int		is_single_quote(char chr);
int		is_double_quote(char chr);

// utils_delimiter.c
int		is_delimiter(char chr);
int		is_space(char chr);
int		is_pipe(char chr);
int		s_dollar(char chr);
int		is_redirect_or_pipe(int type);

// utils_redirect.c
int		is_redirect(char chr);
int		is_redirect_input(char chr);
int		is_redirect_output(char chr);
int		is_heredoc(char chr, char next_chr);
int		is_append(char chr, char next_chr);

// utils_tokens.c
t_node	*print_lst_tokens(t_node *node);

//env_list_utils.c

void	update_env_list(t_list *lst_env, char *name, char *value);

// utils_ft.c
int		ft_strcmp(char	*str1, char *str2);
char	*ft_chrjoin(char *dest, char src);

/* --- parser --- */

//pipe_error.c

int		check_first_pipe(t_list	*lst_tokens);
int		check_last_pipe(t_list	*lst_tokens);
int		check_redirect_after_pipe(t_list	*lst_tokens);

//redirect_error.c

int		find_redirect(int type);
int		output_error(t_list	*lst_tokens);
int		input_error(t_list	*lst_tokens);
int		append_error(t_list	*lst_tokens);
int		heredoc_error(t_list	*lst_tokens);

//syntax_error.c
int		syntax_error(t_list *lst_tokens, t_list	*lst_env, char *input);
int		redirect_error(t_list	*lst_tokens);
int		pipe_error(t_list	*lst_tokens);
int		dot_error(t_list	*lst_tokens);

//parser.c

int		parsing(t_list *lst_tokens, t_list	*lst_env, char *input);

//remove_quotes.c

t_node	*new_str(t_node *node);
char	*create_str(char *str, char *temp, int i, int j);
t_list	*remove_quotes(t_list *lst_tokens);
int		count_characters_inside_quotes(const char *value, int *i,
			char signal, int inside_quotes);
int		count_characters_outside_quotes(const char *value, int *i,
			int inside_quotes);
int		find_new_len(const char *value, int len, int i, int counter);

//path.c

char	**split_path(t_list *lst_env);
int		count_paths(const char *value);
char	*return_value(t_list *lst_env, char *name);
char	*get_path(char *value, int i, int len, int j);
int		get_len(char *value);
void	free_path(char **path);

//list_to_matrix.c

char	**list_to_matrix(t_list *lst_env, int counter, int i);
int		count_nodes(t_list *lst_env);
char	*concatenate(char *s1, char *s2);
void	free_matrix(char **envp);
#endif
