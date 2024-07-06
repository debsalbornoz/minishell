/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:16:31 by jraupp            #+#    #+#             */
/*   Updated: 2024/06/07 23:27:33 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

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
