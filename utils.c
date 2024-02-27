/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:20:14 by dlamark-          #+#    #+#             */
/*   Updated: 2024/02/27 19:22:31 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*create_node(char *str)
{
	t_tokens	*new_node;

	new_node = (t_tokens *)ft_calloc(1, sizeof(t_tokens));
	new_node->str = str;
	new_node->builtin = 0;
	new_node->enabled = 0;
	new_node->type = NULL;
	new_node->option = NULL;
	new_node->value = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_tokens	*append_node(t_tokens **list, char *str)
{
	t_tokens	*new_node;
	t_tokens	*current_node;

	new_node = create_node(str);
	new_node->next = NULL;
	if (*list == NULL)
	{
		new_node->prev = NULL;
		*list = new_node;
	}
	else
	{
		current_node = *list;
		while (current_node->next != NULL)
		{
			current_node = current_node->next;
		}
		current_node->next = new_node;
		new_node->prev = current_node;
	}
	return (new_node);
}

char	*ft_strcpy(char *dst, const char *src, int size)
{
	int	i;

	i = 0;
	if (dst == NULL || src == NULL)
		return (NULL);
	else if (size == 0)
		return (NULL);
	while (i < size && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
