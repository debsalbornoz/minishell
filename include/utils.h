/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 02:44:52 by jackson           #+#    #+#             */
/*   Updated: 2024/05/28 10:55:13 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../library/lib.h"

/* --- source/utils/ --- */
// utils_delimiter.c
int		is_delimiter(char chr);
int		is_space(char chr);
int		is_pipe(char chr);
int		s_dollar(char chr);
int		is_redirect_or_pipe(int type);

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
t_node	*print_lst_tokens(t_node *node);

// utils_builtins.c
int		is_command(int type);
int		is_builtins(int type);

// utils_ft.c
int		ft_strcmp(char	*str1, char *str2);
char	*ft_chrjoin(char *dest, char src);
char	*ft_rmchr(char *input, char *position);

#endif
