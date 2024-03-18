/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:12 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/18 20:43:08 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*trim_start_spaces(char *input)
{
	while (is_space(*input))
		input++;
	return (input);
}

char	process_quotes(char signal, char input)
{
	if (!signal && is_quote(input))
	{
		return (input);
	}
	else if (input == signal)
		return (FALSE);
	return (signal);
}

int	process_delimiter(t_list *tokens, int signal, char *input, int i)
{
	int	j;

	j = 0;
	if (!signal && is_delimiter(input[i]))
	{
		j = 1;
		if (is_redirect(input[i]))
		{
			tokens = process_redirect(tokens, input, i);
			if (is_append(input[i], input[i + 1])
				|| is_heredoc(input[i], input[i + 1]))
				return (2);
		}
		else if (is_pipe(input[i]))
		{
			tokens = add_node(tokens);
			tokens->node->data = ft_calloc(1, sizeof(int));
			tokens->node->value = ft_strdup("|");
			tokens->node->data->type = PIPE;
			if (input[i + 1] != '\0')
				tokens->node->next_chr = ft_strdup(&input[i + 1]);
		}
	}
	return (j);
}
