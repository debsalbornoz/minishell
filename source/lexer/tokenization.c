/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:12 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/11 16:07:23 by jraupp           ###   ########.fr       */
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

int	process_delimiter(t_list *list, int signal, char *input, int i)
{
	if (!signal && is_delimiter(input[i]))
	{
		if (is_redirect(input[i]))
		{
			list = process_redirect(list, input, i);
			if (is_append(input[i], input[i + 1])
				|| is_heredoc(input[i], input[i + 1]))
				return (TRUE);
		}
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
	return (FALSE);
}
