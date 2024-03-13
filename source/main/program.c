/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:46:23 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/12 21:48:38 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	program(void)
{
	t_list	list;
	char	*input;

	input = readline("¯\\_(ツ)_/¯: ");
	if (!*input)
	{
		free(input);
		return (FALSE);
	}
	list = *init_list(&list);
	list = *tokenization(&list, input);
	type_assignment(&list);
	print_list(&list);
	free(input);
	free_list(&list);
	return (FALSE);
}

t_list	*tokenization(t_list *list, char *input)
{
	char	signal;
	int		i;
	int		input_len;
	int		len;

	signal = 0;
	i = 0;
	input = trim_start_spaces(input);
	input_len = ft_strlen(input);
	while (i < input_len)
	{
		signal = process_quotes(signal, input[i]);
		len = form_word(list, signal, input, i);
		if (signal)
			signal = '\0';
		if (len >= 0 && i + len <= input_len)
			i += len;
		else
			break ;
		if (i + 1 <= input_len)
			i += process_delimiter(list, signal, input, i);
		i++;
	}
	return (list);
}
