/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:15:05 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/09 15:21:01 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int is_heredoc(char chr , char next_chr)
{
	if(is_redirect_input(chr) && is_redirect_input(next_chr))
		return(1);
	return(0);
}

int is_append(char chr , char next_chr)
{
		if(is_redirect_output(chr) && is_redirect_output(next_chr))
		return(1);
	return(0);
}