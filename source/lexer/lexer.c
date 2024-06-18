/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:12 by jraupp            #+#    #+#             */
/*   Updated: 2024/06/15 18:55:11 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*lexer(t_list *tokens, char *input)
{
	char	signal;
	int		i;
	int		token_len;

	signal = 0;
	i = 0;
	if (ft_strlen(input) == 0)
		return (NULL);
	while (i < ft_strlen(input))
	{
		signal = process_quotes(signal, input[i]);
		token_len = process_word(tokens, signal, input, i);
		if (signal)
			signal = '\0';
		if (token_len >= 0 && i + token_len <= ft_strlen(input))
			i += token_len;
		else
			break ;
		if (i + 1 <= ft_strlen(input))
			i += process_delimiter(tokens, signal, input, i);
		if (input[i] == ' ' && input[i] != '\0')
			i++;
	}
	return (tokens);
}

char	*trim_start_spaces(char *input)
{
	int		i;
	char	*trimmed_input;
	int		len;

	len = ft_strlen(input);
	trimmed_input = NULL;
	i = 0;
	while (input[i] == ' ' || input[i] == '	')
		i++;
	if (i > 0 && len - i >= 0)
	{
		trimmed_input = ft_calloc((len - i + 1), sizeof(char));
		len = len - i + 1;
		ft_strlcpy(trimmed_input, &input[i], len);
		//free (input);
		return (trimmed_input);
	}
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
