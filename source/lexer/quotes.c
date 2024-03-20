/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:11:04 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/20 11:49:17 by jraupp           ###   ########.fr       */
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
		if (input[i] == '\'' || input[i] == '"')
		{
			signal = input[i];
			if (input[i + 1] != '\0')
				i++;
		}
		while (input[i] != '\0' && input[i] != signal)
			i++;
		if (input[i] == signal)
			signal = 0;
		if (input[i] != '\0')
			i++;
	}
	if (signal)
		return (0);
	return (1);
}
