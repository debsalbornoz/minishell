/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:15:05 by jraupp            #+#    #+#             */
/*   Updated: 2024/06/07 23:27:41 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	is_redirect(char chr)
{
	return (is_redirect_input(chr) || is_redirect_output(chr));
}

int	is_redirect_input(char chr)
{
	return (chr == '<');
}

int	is_redirect_output(char chr)
{
	return (chr == '>');
}

int	is_heredoc(char chr, char next_chr)
{
	return (is_redirect_input(chr) && is_redirect_input(next_chr));
}

int	is_append(char chr, char next_chr)
{
	return (is_redirect_output(chr) && is_redirect_output(next_chr));
}
