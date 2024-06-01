/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:53:10 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/01 16:39:49 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

typedef struct s_list		t_list;
typedef struct s_node		t_node;
union						u_data;
typedef struct s_token		t_token;
typedef struct s_env		t_env;
typedef struct s_exp		t_exp;
typedef struct s_exec		t_exec;

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
	t_exec	*exec;
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
	char			**redir_and_files;
	char			**eofs;
	int				input;
	int				output;
	int				index;
};

#endif
