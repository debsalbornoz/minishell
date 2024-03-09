/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:12 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/09 17:31:33 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*trim_start_spaces(char *input)
{
	while (is_space(*input))
		input++;
	return (input);
}

char	process_quotes(int signal, char input)
{
	if (!signal && is_quote(input))
		return (input);
	else if (input == signal)
		return (FALSE);
	return (signal);
}

void	process_delimiter(t_list *list, int signal, char *input, int i)
{

	if (!signal && is_delimiter(input[i]))
	{
		if (is_redirect(input[i]))
			list = process_redirect(list, input, i);
		else if (is_dollar(input[i]))
		{
			list = add_node(list, "$");
			list->node->dollar = YES;
		}
		else if (is_pipe(input[i]))
		{
			list = add_node(list, "|");
			list->node->pipe = YES;
		}
	}
}