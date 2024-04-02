/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:35:20 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/01 20:53:07 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	form_word(t_list *lst_tokens, int signal, char *input, int i)
{
	int		len;
	char	*temp;

	len = find_len(&input[i], signal);
	if (len > 0)
	{
		temp = ft_calloc((len + 1), sizeof(char));
		ft_strlcpy(temp, &input[i], len + 1);
		lst_tokens = add_node(lst_tokens);
		lst_tokens->node->data = ft_calloc(1, sizeof(union u_data));
		lst_tokens->node->data->token = ft_calloc(1, sizeof(t_token));
		lst_tokens->node->data->token->value = ft_strdup(temp);
		lst_tokens->node->data->token->type = WORD;
		if (input[len] != '\0')
		{
			if (input[len + 1] != '\0')
				lst_tokens->node->data->token->next_chr = input[i];
		}
		free(temp);
	}
	else
		temp = NULL;
	return (len);
}

int find_len(char *input, int signal) {
    int i = 0;
    int inside_quotes = 0;
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
            break;
        i++;
    }
    return i;
}