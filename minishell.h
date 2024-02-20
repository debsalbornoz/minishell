/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:56:32 by dlamark-          #+#    #+#             */
/*   Updated: 2024/02/20 18:13:17 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

enum				e_tokentype
{
	FILES,
	COMMAND,
	ARGUMENT,
	STRING,
	VARIABLE,
	PIPE,
	REDIRECT,
};

typedef struct s_tokens
{
	char			*str;
	char			*type;
	char			*option;
	char			*value;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}					t_tokens;

typedef struct s_env
{
	int				env_variable;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

t_tokens			*create_node(char *str);
void				add_node(t_tokens **list, char *str);
void				init_tokenization(t_tokens **list, char *str);
int					find_redirect(char *str);
void				add_redirect(t_tokens **list, char *str);

#endif