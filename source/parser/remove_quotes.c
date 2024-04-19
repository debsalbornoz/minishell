/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:07:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/10 20:27:30 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*remove_quotes(t_list *lst_tokens)
{
	if (!lst_tokens || !lst_tokens->node)
		return (NULL);
	while (lst_tokens->node)
	{
		lst_tokens->node = new_str(lst_tokens->node);
		printf("%s\n", lst_tokens->node->data->token->value);
		lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (lst_tokens);
}

t_node	*new_str(t_node *node)
{
	char	*temp;
	char	*str;
	int		len;

	temp = NULL;
	str = node->data->token->value;
	len = find_new_len(node->data->token->value,
			ft_strlen(node->data->token->value), 0, 0);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return (NULL);
	temp = create_str(str, temp, 0, 0);
	free(node->data->token->value);
	node->data->token->value = ft_strdup(temp);
	free(temp);
	return (node);
}

char	*create_str(char *str, char *temp, int i, int j)
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

int	find_new_len(const char *value, int len, int i, int counter)
{
	char	signal;
	int		inside_quotes;

	signal = '\0';
	inside_quotes = 0;
	while (i < len)
	{
		if (is_quote(value[i]))
		{
			signal = value[i];
			inside_quotes = 1;
			i++;
		}
		counter += count_characters_inside_quotes(value, &i,
				signal, inside_quotes);
		if (value[i] == signal)
		{
			signal = '\0';
			inside_quotes = 0;
		}
		counter += count_characters_outside_quotes(value, &i, inside_quotes);
		i++;
	}
	return (counter);
}
