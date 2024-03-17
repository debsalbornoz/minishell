/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:24 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/17 13:52:34 by jraupp           ###   ########.fr       */
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

typedef struct s_list	t_list;
typedef struct s_node	t_node;
union					u_data;

struct s_list
{
	t_node			*node;
	struct s_node	*head;
};

struct s_node
{
	char			*value;
	union u_data	*data;
	struct s_node	*next;
};

union u_data
{
	int				type;
	char			*name;
};

/* --- source/main --- */
// program.c
int			program(void);
t_list		*tokenization(t_list *list, char *input);

// linked_list.c
t_list		*add_node(t_list *list);
void		print_list(t_list *tokens, void (f)(t_node *));
void		free_list(t_list *list, void (f)(t_list *));
void		free_tokens(t_list *tokens);
void		free_env_list(t_list *env_list);

//env_list.c
t_list		*make_env_list(char **envp, t_list *env_list);
char		*find_name(char *envp);
char		*find_value(char *envp);
void		print_env_list(t_node *variable);

/* --- source/lexer/ --- */
// tokenization.c
char		*trim_start_spaces(char *input);
char		process_quotes(char signal, char input);
int			process_delimiter(t_list *tokens, int signal, char *input, int i);

// redirect.c
t_list		*process_redirect(t_list *tokens, char *input, int i);
t_list		*process_redirect_input(t_list *tokens, char *input, int i);
t_list		*process_redirect_output(t_list *tokens, char *input, int i);

// forme_word.c
int			form_word(t_list *tokens, int signal, char *input, int i);
int			find_len(char *input, int signal);

//type assignment.C
t_list		*type_assignment(t_list *tokens);

//commands.c
t_list		*is_command(t_list *tokens);
int			ft_strlcmp(char *s1, char *s2, int len);
int			compare_quoted_strings(char *s1, char *s2);
t_list		*is_builtin(t_list *tokens);

//files.c
t_list		*is_file(t_list *tokens);
t_list		*is_heredoc_key(t_list *tokens);

/* --- source/utils/ --- */
// utils_quote.c
int			is_quote(char chr);
int			is_single_quote(char chr);
int			is_double_quote(char chr);

// utils_delimiter.c
int			is_delimiter(char chr);
int			is_space(char chr);
int			is_pipe(char chr);
int			s_dollar(char chr);
int			is_redirect_or_pipe(int type);

// utils_redirect.c
int			is_redirect(char chr);
int			is_redirect_input(char chr);
int			is_redirect_output(char chr);
int			is_heredoc(char chr, char next_chr);
int			is_append(char chr, char next_chr);

//utils_tokens.c
void		print_tokens(t_node *token);

#endif
