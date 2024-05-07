/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:12 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/07 18:44:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_closed(char *input)
{
	char	signal;
	int		i;

	signal = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (is_quote(input[i]) && !signal)
		{
			signal = input[i];
			i++;
		}
		if (input[i] == signal)
			signal = 0;
		i++;
	}
	if (signal)
	{
		printf("Fatal error: unclosed quotes\n");
		return (0);
	}
	return (1);
}
int	count_characters_inside_quotes(const char *str, int *i,
char signal, int inside_quotes)
{
	int	counter;

	counter = 0;
	while (inside_quotes && str[*i] != signal && str[*i] != '\0')
	{
		(*i)++;
		counter++;
	}
	return (counter);
}

int	count_characters_outside_quotes(const char *str, int *i,
int inside_quotes)
{
	int	counter;

	counter = 0;
	if (!inside_quotes && str[*i] != '\0' && !is_quote(str[*i]))
		counter++;
	return (counter);
}
