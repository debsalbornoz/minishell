/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:12 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/10 20:02:41 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
