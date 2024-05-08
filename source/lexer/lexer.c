/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:12 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/06 14:13:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*lexer(t_list *tokens, char *input)
{
	char	signal;
	int		i;
	int		input_len;
	int		token_len;

	signal = 0;
	i = 0;
	input = trim_start_spaces(input);
	input_len = ft_strlen(input);
	while (i < input_len)
	{
		signal = process_quotes(signal, input[i]);
		token_len = process_word(tokens, signal, input, i);
		if (signal)
			signal = '\0';
		if (token_len >= 0 && i + token_len <= input_len)
			i += token_len;
		else
			break ;
		if (i + 1 <= input_len)
			i += process_delimiter(tokens, signal, input, i);
		if (input[i] == ' ' && input[i] != '\0')
			i++;
	}
	return (tokens);
}

char	*trim_start_spaces(char *input)
{
	while (is_space(*input))
		input++;
	return (input);
}

char	process_quotes(char signal, char input)
{
	if (!signal && is_quote(input))
		return (input);
	else if (input == signal)
		return (FALSE);
	return (signal);
}
