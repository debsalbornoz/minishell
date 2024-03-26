/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:46:23 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/25 19:07:01 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	program(t_list *lst_env)
{
	t_list		lst_tokens;
	char		*input;

	(void)lst_env;
	input = readline("¯\\_(ツ)_/¯: ");
	if (!input)
	{
		free(input);
		return (FALSE);
	}
	lst_tokens.node = 0;
	if (!is_closed(input))
		exit (1);
	lst_tokens = *tokenization(&lst_tokens, input);
	lst_tokens = *type_assignment(&lst_tokens);
	runs_on_list(&lst_tokens, print_lst_tokens);
	free_list(&lst_tokens, free_lst_tokens);
	free(input);
	return (TRUE);
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
		if (input[i] == ' ')
			i++;
	}
	return (lst_tokens);
}
