/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:24 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/09 17:31:38 by dlamark-         ###   ########.fr       */
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

enum	e_type_status
{
	NO,
	YES
};

enum	e_type_builtin
{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	OTHER
};

enum	e_type_redirects
{
	INPUT = 1,
	OUTPUT,
	APPEND,
	HEREDOC
};

typedef struct s_node
{
	char			*value;
	int				arg;
	int				file;
	int				pipe;
	int				dollar;
	int				command;
	int				redirect;
	struct s_node	*next;
	struct s_node	*prev;
}t_node;

typedef struct s_list
{
	t_node			*node;
	struct s_node	*head;
	struct s_node	*tail;
}t_list;

/* --- source/main --- */
// program.c
char	*receive_input(void);
int		program(void);
t_list	*tokenization(t_list *list, char *input);
// linked_list.c
t_list	*init_list(t_list *list);
t_list	*add_node(t_list *list, char *value);
void	print_list(t_list *list);
void	free_list(t_list *list);

/* --- source/lexer/ --- */
// tokenization.c
char	*trim_start_spaces(char *input);
char	process_quotes(int signal, char input);
int	process_delimiter(t_list *list, int signal, char *input, int i);

// redirect.c
t_list *process_redirect(t_list *list, char *input, int i);
t_list *process_redirect_input(t_list *list, char *input, int i);
t_list *process_redirect_output(t_list *list, char *input, int i);

// forme_word.c
char	*ft_strjoinchr(char *str, char chr);
int form_word(t_list *list, int signal, char *input, int i);

/* --- source/utils/ --- */
// utils_quote.c
int		is_quote(char chr);
int		is_single_quote(char chr);
int		is_double_quote(char chr);

// utils_delimiter.c
int		is_delimiter(char chr);
int		is_space(char chr);
int		is_pipe(char chr);
int		is_dollar(char chr);

// utils_redirect.c
int		is_redirect(char chr);
int		is_redirect_input(char chr);
int		is_redirect_output(char chr);
int 	is_heredoc(char chr , char next_chr);
int 	is_append(char chr , char next_chr);

//teste

int find_len(char *input, int signal);

#endif
