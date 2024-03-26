/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:12 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/20 20:04:10 by jraupp           ###   ########.fr       */
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
		return (input);
	else if (input == signal)
		return (FALSE);
	return (signal);
}

int	process_delimiter(t_list *lst_tokens, int signal, char *input, int i)
{
	int	j;

	j = 0;
	if (!signal && is_delimiter(input[i]))
	{
		j = 1;
		if (is_redirect(input[i]))
		{
			lst_tokens = process_redirect(lst_tokens, input, i);
			if (is_append(input[i], input[i + 1])
				|| is_heredoc(input[i], input[i + 1]))
				return (2);
		}
		else if (is_pipe(input[i]))
		{
			lst_tokens = add_node(lst_tokens);
			lst_tokens->node->data = ft_calloc(1, sizeof(union u_data));
			lst_tokens->node->data->token = ft_calloc(1, sizeof(t_token));
			lst_tokens->node->data->token->value = ft_strdup("|");
			lst_tokens->node->data->token->type = PIPE;
		}
	}
	return (j);
}
