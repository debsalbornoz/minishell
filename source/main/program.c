/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:46:23 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/11 18:07:04 by jraupp           ###   ########.fr       */
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
	print_list(&list);
	free(input);
	free_list(&list);
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
		if (len >= 0 && i + len <= input_len)
			i += len;
		else
			break ;
		if (i + 1 < input_len)
			i += process_delimiter(list, signal, input, i);
		i++;
	}
	return (list);
}
