/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:16:31 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/07 18:43:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_quote(char chr)
{
	return (is_single_quote(chr) || is_double_quote(chr));
}

int	is_single_quote(char chr)
{
	return (chr == '\'');
}

int	is_double_quote(char chr)
{
	return (chr == '\"');
}

