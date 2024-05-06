/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:12 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/22 14:51:17 by codespace        ###   ########.fr       */
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
