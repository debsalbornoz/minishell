/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:07:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/08/04 10:51:04 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*remove_quotes(t_list *tokens)
{
	t_node	*aux;

	aux = tokens->head;
	if (!tokens || !tokens->node)
		return (NULL);
	while (aux)
	{
		aux = replace_str(aux);
		aux = aux->next;
	}
	return (tokens);
}

t_node	*replace_str(t_node *node)
{
	char	*new_str;
	char	*token;
	int		len;

	new_str = NULL;
	token = node->data->token->value;
	len = find_new_len(node->data->token->value,
			ft_strlen(node->data->token->value), 0, 0);
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	new_str = unquote_str(token, new_str, 0, 0);
	free(node->data->token->value);
	node->data->token->value = ft_strdup(new_str);
	free(new_str);
	return (node);
}

char	*unquote_str(char *str, char *temp, int i, int j)
{
	char	signal;
	int		inside_quotes;

	signal = '\0';
	inside_quotes = 0;
	while (str[i] != '\0')
	{
		if (is_quote(str[i]))
		{
			signal = str[i];
			inside_quotes = 1;
			i++;
		}
		while (inside_quotes && str[i] != signal && str[i] != '\0')
			temp[j++] = str[i++];
		if (str[i] == signal)
		{
			signal = '\0';
			inside_quotes = 0;
			i++;
		}
		if (!signal && !inside_quotes && str[i] != '\0' && !is_quote(str[i]))
			temp[j++] = str[i++];
	}
	return (temp);
}

int	find_new_len(const char *str, int len, int i, int counter)
{
	char	signal;
	int		inside_quotes;

	signal = '\0';
	inside_quotes = 0;
	while (i < len)
	{
		if (is_quote(str[i]))
		{
			signal = str[i];
			inside_quotes = 1;
			i++;
		}
		counter += count_characters_inside_quotes(str, &i,
				signal, inside_quotes);
		if (str[i] == signal)
		{
			signal = '\0';
			inside_quotes = 0;
		}
		counter += count_characters_outside_quotes(str, &i, inside_quotes);
		i++;
	}
	return (counter);
}
