/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:46:23 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/09 18:16:52 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>

int		program(void)
{
	t_list	list;
	char	*input;

	input = readline("¯\\_(ツ)_/¯: ");
	if (!*input)
		return (FALSE);
	list = *init_list(&list);
	list = *tokenization(&list, input);
	print_list(&list);
	free_list(&list);
	return (FALSE);
}

// t_list *tokenization(t_list *list, char *input)
// {
// 	char signal;
// 	char *temp;
// 	char len;
// 	int i;
// 	int len_word;

// 	temp = NULL;
// 	signal = 0;
// 	i = 0;
// 	len = 0;
	
// 	input = trim_start_spaces(input);
// 	len_word = ft_strlen(input);
// 	while (input[i] != '\0')
//     {
// 		signal = process_quotes(signal, input[i]);
// 		len = form_word(list, signal, input, temp, i);
// 		if( i + len <= len_word)
// 			i+= len;
// 		process_delimiter(list, signal, input, i);
// 		if(input[i] != '\0' && input[i + 1] != '\0' )
// 		{
// 			if (is_heredoc(input[i], input[i + 1]) || is_append(input[i], input[i + 1]))
// 			i++;
// 		}

// 		//temp = form_word(list, signal, input, &temp, i);
// 		i++;
// 	}
// 	free(temp);
// 	return (list);
// }

t_list *tokenization(t_list *list, char *input)
{
	char signal;
	char *temp = NULL;
	int i = 0;
	int len_word;

	temp = NULL;
	signal = 0;
	i = 0;

	input = trim_start_spaces(input);
	len_word = ft_strlen(input);

	while (i < len_word)
	{
		signal = process_quotes(signal, input[i]);
		int len = form_word(list, signal, input, temp, i);
		if (len >= 0 && i + len <= len_word)
			i += len;
		else
			break;
		process_delimiter(list, signal, input, i);
		if (i + 1 < len_word)
		{
			if (is_heredoc(input[i], input[i + 1]) || is_append(input[i], input[i + 1]))
				i++;
		}
		i++;
	}

	free(temp);
	return list;
}
