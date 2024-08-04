/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:12 by jraupp            #+#    #+#             */
/*   Updated: 2024/08/04 10:50:54 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_closed(char *input, t_list *envp)
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
			if (input[i + 1] != '\0')
				i++;
			else
				break ;
		}
		if (input[i] != '\0' && input[i] == signal)
			signal = 0;
		i++;
	}
	if (signal)
	{
		print_fatal_error(input, envp);
		return (0);
	}
	return (1);
}

void	print_fatal_error(char *input, t_list *envp)
{
	ft_putstr_fd("Fatal error: unclosed quotes\n", 2);
	update_env_list(envp, "?", "2");
	free(input);
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
