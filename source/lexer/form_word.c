/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:35:20 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/26 20:23:07 by jraupp           ###   ########.fr       */
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

int	find_len(char *input, int signal)
{
	int	i;

	i = 0;
	if (signal)
	{
		i = 1;
		while (input[i] != '\0' && input[i] != signal)
			i++;
		if (input[i] == signal)
			i++;
	}
	else
	{
		while (input[i] != '\0' && !is_delimiter(input[i]))
			i++;
	}
	return (i);
}
