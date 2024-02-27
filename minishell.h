/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:56:32 by dlamark-          #+#    #+#             */
/*   Updated: 2024/02/27 20:26:43 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_tokens
{
	char			*str;
	char			*type;
	char			*option;
	char			*value;
	bool			enabled;
	char			*builtin;
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
void				tokenize_input(t_tokens **list, char *str);;
t_tokens			*create_node(char *str);
t_tokens			*append_node(t_tokens **list, char *str);
void				add_pipe(t_tokens **list, char *str);
void				add_redirect(t_tokens **list, char *str, char c);
void				add_multi_redirect(t_tokens **list, char *str, char c);
int					find_len(char *str);
char				*ft_strcpy(char *dst, const char *src, int size);
void				add_word(t_tokens **list, char *str, char *s, int len);
int					is_builtin( char *s1);
int					ft_strcmp(const char *s1, const char *s2, int n);
void				enable_builtin(t_tokens **list);	
#endif