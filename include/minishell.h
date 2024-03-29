/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:24 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/29 17:39:15 by jraupp           ###   ########.fr       */
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

/* --- source/main --- */
// env_list.c
t_list	*make_lst_env(char **envp, t_list *lst_env);
char	*find_name(char *envp);
char	*find_value(char *envp);
t_node	*print_lst_env(t_node *node);

// expand_part1.c
char	*expand(t_list *lst_env, char *input);

// expand_part2.c
char	*var_expand(char *input, char *position, char *name, char *value);

// program.c
int		program(t_list *lst_env);
t_list	*tokenization(t_list *lst_tokens, char *input);

// linked_list.c
t_list	*add_node(t_list *list);
t_list	*runs_on_list(t_list *list, t_node *(f)(t_node *));

// free_list.c
void	free_list(t_list *list, void (f)(t_list *));
void	free_lst_tokens(t_list *tokens);
void	free_lst_env(t_list *env_list);

//signals.c
void	handle_sigint(int signal);
void	handle_signal(void);
void	set_error(t_list *lst_env);

/* --- source/lexer/ --- */
// tokenization.c
char	*trim_start_spaces(char *input);
char	process_quotes(char signal, char input);
int		process_delimiter(t_list *lst_tokens, int signal, char *input, int i);

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
t_list	*data_env_addr(void);

// utils_ft.c
int		ft_strcmp(char	*str1, char *str2);
char	*ft_chrjoin(char *dest, char src);

/* --- parser --- */
//syntax_error.c

t_list	*pipe_error(t_list	*lst_tokens, t_list	*lst_env);
int		is_redirect_2(int type);
t_list	*output_error(t_list	*lst_tokens, t_list	*lst_env);
t_list	*syntax_error(t_list *lst_tokens, t_list	*lst_env);

#endif
