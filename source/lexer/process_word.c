/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:35:20 by jraupp            #+#    #+#             */
/*   Updated: 2024/07/09 18:19:44 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_word(t_list *lst_tokens, int signal, char *input, int i)
{
	int		token_len;
	char	*word;
	int		empty_quotes;

	empty_quotes = 0;
	if (input[i + is_empty_quotes(signal, &input[i])] != '\0')
		i = i + empty_quotes;
	token_len = get_token_len(&input[i], signal, 0);
	if (token_len > 0)
	{
		word = ft_calloc((token_len + 1), sizeof(char));
		ft_strlcpy(word, &input[i], token_len + 1);
		lst_tokens = add_node(lst_tokens);
		lst_tokens->node->data = ft_calloc(1, sizeof(union u_data));
		lst_tokens->node->data->token = ft_calloc(1, sizeof(t_token));
		lst_tokens->node->data->token->value = ft_strdup(word);
		lst_tokens->node->data->token->type = WORD;
		free(word);
	}
	else
		word = NULL;
	return (token_len);
}

int	get_token_len(char *input, int signal, int inside_quotes)
{
	int	i;

	i = -1;
	if (signal)
	{
		i++;
		inside_quotes = 1;
	}
	while (input[++i] != '\0')
	{
		if (is_quote(input[i]) && !signal)
		{
			signal = input[i];
			inside_quotes = !inside_quotes;
		}
		else if (input[i] == signal)
		{
			signal = 0;
			inside_quotes = !inside_quotes;
		}
		else if (!inside_quotes && is_delimiter(input[i]))
			break ;
	}
	return (i);
}

int	is_empty_quotes(char signal, char *input)
{
	int	i;

	i = 0;
	if (signal && input[i + 1] == signal)
		return (2);
	return (0);
}
