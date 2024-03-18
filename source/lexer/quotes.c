/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:11:04 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/18 20:46:21 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_closed(char *input)
{
	char		signal;
	int			i;

	signal = 0;
	i = -1;
	while (input[i++] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			signal = input[i];
			if (input[i + 1] != '\0')
				i++;
		}
		while (input[i] != signal && input[i] != '\0')
			i++;
		if (input[i] == signal)
		{
			signal = 0;
			if (input[i + 1] != '\0')
				i++;
		}
	}
	if (signal)
		return (0);
	return (1);
}
