/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:12 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/11 21:25:27 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*trim_start_spaces(char *input)
{
	while (is_space(*input))
		input++;
	return (input);
}

char	process_quotes(char  signal, char input, char *str, int i)
{
	if (!signal && is_quote(input))
	{
		if(is_closed(signal, str, i))
			return (input);
		else
			exit(1);
	}
	else if (input == signal)
		return (FALSE);
	return (signal);
}

int is_closed(char signal, char *str, int i)
{

	while(str[i] != '\0')
	{
		if(str[i] == signal)
			return(1);
		i++;
	}
	return(0);
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
		else if (is_pipe(input[i]))
		{
			list = add_node(list, "|");
			list->node->type = PIPE;
		}
	}
	return (FALSE);
}
