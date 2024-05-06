/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:35:20 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/06 14:11:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_word(t_list *lst_tokens, int signal, char *input, int i)
{
	int		token_len;
	char	*word;

	token_len = get_token_len(&input[i], signal);
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

int	get_token_len(char *input, int signal)
{
	int	i;
	int	inside_quotes;

	i = 0;
	inside_quotes = 0;
	while (input[i] != '\0')
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
		i++;
	}
	return (i);
}
