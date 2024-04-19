/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:16:31 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/06 17:12:45 by dlamark-         ###   ########.fr       */
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

int	count_characters_inside_quotes(const char *value, int *i,
char signal, int inside_quotes)
{
	int	counter;

	counter = 0;
	while (inside_quotes && value[*i] != signal && value[*i] != '\0')
	{
		(*i)++;
		counter++;
	}
	return (counter);
}

int	count_characters_outside_quotes(const char *value, int *i,
int inside_quotes)
{
	int	counter;

	counter = 0;
	if (!inside_quotes && value[*i] != '\0' && !is_quote(value[*i]))
		counter++;
	return (counter);
}
