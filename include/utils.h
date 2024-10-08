/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:53:28 by dlamark-          #+#    #+#             */
/*   Updated: 2024/08/02 16:53:01 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../library/lib.h"

int		is_delimiter(char chr);
int		is_space(char chr);
int		is_pipe(char chr);
int		s_dollar(char chr);
int		is_redirect_or_pipe(int type);

int		is_quote(char chr);
int		is_single_quote(char chr);
int		is_double_quote(char chr);

int		is_redirect(char chr);
int		is_redirect_input(char chr);
int		is_redirect_output(char chr);
int		is_heredoc(char chr, char next_chr);
int		is_append(char chr, char next_chr);

int		is_command(int type);
int		is_builtins(int type);
int		is_valid_first_char(char chr);
int		is_valid_char(char chr);

int		ft_strcmp(char	*str1, char *str2);
char	*ft_chrjoin(char *dest, char src);
char	*ft_rmchr(char *input, char *position);
int		ft_str_exist(char *sting);
int		ft_free_str(char *str);

#endif
