/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:16:31 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/07 12:17:02 by jraupp           ###   ########.fr       */
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
