/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:46:23 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/06 14:47:22 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	program(t_list *lst_env)
{
	t_list		lst_tokens;
	char		*input;

	lst_tokens.node = 0;
	input = readline("¯\\_(ツ)_/¯: ");
	if (check_input(input) == 0)
		return (FALSE);
	if (check_input(input) == 1)
		return (TRUE);
	lst_tokens = *lexical_analysis(input, &lst_tokens);
	if (!parsing(&lst_tokens, lst_env, input))
		return (TRUE);
	free_list(&lst_tokens, free_lst_tokens);
	free(input);
	return (FALSE);
}

t_list	*tokenization(t_list *lst_tokens, char *input)
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
		len = form_word(lst_tokens, signal, input, i);
		if (signal)
			signal = '\0';
		if (len >= 0 && i + len <= input_len)
				i += len;
		else
			break ;
		if (i + 1 <= input_len)
			i += process_delimiter(lst_tokens, signal, input, i);
		if (input[i] == ' ' && input[i] != '\0')
			i++;
	}
	return (lst_tokens);
}
