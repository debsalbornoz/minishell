/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:24 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/12 21:47:32 by dlamark-         ###   ########.fr       */
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

enum	e_type_exit
{
	CONTINUE,
	STOP
};

enum	e_type_signal
{
	FALSE,
	TRUE
};

enum	e_type_type
{
	DELIMITER = 1000,
	REDIRECT = 1100,
	INPUT = 1110 ,
	HEREDOC = 1120 ,
	OUTPUT = 1130 ,
	APPEND = 1140 ,
	PIPE = 1200 ,
	WORD = 2000 ,
	COMMAND = 2100 ,
	EXECUTABLE = 2110 ,
	BUILTIN = 2120 ,
	ECHO = 2121 ,
	CD = 2122,
	PWD = 2123 ,
	EXPORT = 2124,
	UNSET = 2125,
	ENV = 2126 ,
	EXIT = 2127 ,
	ARGUMENT = 2200 ,
	FILES = 2210 ,
	INPUT_FILE = 2211 ,
	OUTPUT_FILE = 2212,
	FLAG = 2220 ,
	HEREDOC_KEY = 2230 ,
	VARIABLE = 2300
};

typedef struct s_node_token
{
	char				*value;
	int					type;
	struct s_node_token	*next;
	struct s_node_token	*prev;
}t_node_token;

typedef struct s_list
{
	t_node_token			*node;
	struct s_node_token		*head;
	struct s_node_token		*tail;
}t_list;

typedef struct s_node_env
{
	char				*name;
	char				*value;
	struct s_node_env	*next;
}t_node_env;

typedef struct s_env_list
{
	t_node_env				*node;
	struct s_node_env		*head;
	struct s_node_env		*tail;
}t_env_list;

/* --- source/main --- */
// program.c
char		*receive_input(void);
int			program(void);
t_list		*tokenization(t_list *list, char *input);
// linked_list.c
t_list		*init_list(t_list *list);
t_list		*add_node(t_list *list, char *value);
void		print_list(t_list *list);
void		free_list(t_list *list);

/* --- source/lexer/ --- */
// tokenization.c
char		*trim_start_spaces(char *input);
char	process_quotes(char  signal, char input, char *str, int i);
int			process_delimiter(t_list *list, int signal, char *input, int i);

// redirect.c
t_list		*process_redirect(t_list *list, char *input, int i);
t_list		*process_redirect_input(t_list *list, char *input, int i);
t_list		*process_redirect_output(t_list *list, char *input, int i);

// forme_word.c
char		*ft_strjoinchr(char *str, char chr);
int			form_word(t_list *list, int signal, char *input, int i);
int			find_len(char *input, int signal);
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

// utils_redirect.c
int			is_redirect(char chr);
int			is_redirect_input(char chr);
int			is_redirect_output(char chr);
int			is_heredoc(char chr, char next_chr);
int			is_append(char chr, char next_chr);

//env_list

char		*find_name(char *envp);
char		*find_value(char *envp);
t_env_list	*init_env_list(t_env_list *list);
t_env_list	*add_env_node(t_env_list *list, char *name, char *value);
void		print_env_list(t_env_list *list);
t_env_list	*make_env_list(char **envp, t_env_list *env_list);

//type assignment

void		is_command(t_list *tokens);
void		is_argument(t_list *tokens);
void		type_assignment(t_list *tokens);
void 		is_builtin(t_list *tokens);
int 		ft_strlcmp(char *s1, char *s2);
int			is_closed(char signal, char *str, int i);
#endif
