/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:07:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/03 20:03:06 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*new_str(t_node *node)
{
	char	*temp;
	char	*str;
	int		len;

	temp = NULL;
	str = node->data->token->value;
	len = find_new_len(node);
	temp = ft_calloc(len + 1, sizeof(char));
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

int	find_new_len(t_node *node)
{
	char	*str;
	int		counter;
	char	signal;
	int		i;
	int		inside_quotes;

	str = node->data->token->value;
	counter = 0;
	signal = '\0';
	i = 0;
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
		{
			i++;
			counter++;
		}
		if (str[i] == signal)
		{
			signal = '\0';
			inside_quotes = 0;
			i++;
		}
		if (!signal && !inside_quotes && str[i] != '\0' && !is_quote(str[i]))
		{
			counter++;
			i++;
		}
	}
	return (counter);
}

t_list	*remove_quotes(t_list *lst_tokens)
{
	while (lst_tokens->node)
	{
		lst_tokens->node = new_str(lst_tokens->node);
		printf("%s\n", lst_tokens->node->data->token->value);
		lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (lst_tokens);
}
