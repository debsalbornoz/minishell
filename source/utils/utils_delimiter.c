/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:46:06 by jraupp            #+#    #+#             */
/*   Updated: 2024/06/07 23:27:13 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	is_delimiter(char chr)
{
	return (is_space(chr) || is_redirect(chr)
		|| is_pipe(chr));
}

int	is_space(char chr)
{
	return (chr == ' ' || chr == '\t');
}

int	is_pipe(char chr)
{
	return (chr == '|');
}

int	is_dollar(char chr)
{
	return (chr == '$');
}

int	is_redirect_or_pipe(int type)
{
	return (type == PIPE
		|| type == INPUT || type == HEREDOC
		|| type == OUTPUT || type == APPEND);
}
