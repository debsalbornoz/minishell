/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:46:23 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/17 14:14:20 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	program(void)
{
	t_list	tokens;
	char	*input;

	input = readline("¯\\_(ツ)_/¯: ");
	if (!*input)
	{
		free(input);
		return (FALSE);
	}
	tokens.node = 0;
	tokens = *tokenization(&tokens, input);
	tokens = *type_assignment(&tokens);
	print_list(&tokens, print_tokens);
	free_list(&tokens, free_tokens);
	free(input);
	return (TRUE);
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
		if (input[i] == ' ')
			i++;
	}
	return (list);
}
