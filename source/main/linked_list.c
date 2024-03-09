/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:51:10 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/09 15:31:50 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*init_list(t_list *list)
{
	list->node = 0;
	list->head = list->node;
	list->tail = list->node;
	return (list);
}

t_list	*add_node(t_list *list, char *value)
{
	if (!list->node)
	{
		list->node = ft_calloc (1, sizeof(t_node));
		list->head = list->node;
	}
	else
	{
		list->node = list->tail;
		list->node->next = ft_calloc (1, sizeof(t_node));
		list->node = list->node->next;
	}
	list->tail = list->node;
	list->node->value = value;
	return (list);
}

void	print_list(t_list *list)
{
	if (list->node)
	{
		list->node = list->head;
		while (list->node && list->node->next)
		{
			printf("%s\n", list->node->value);
			list->node = list->node->next;
		}
		printf("%s\n", list->node->value);
	}
}

void	free_list(t_list *list)
{
	if (list->node)
	{
		list->node = list->head;
		while (list->node && list->node->next)
		{
			list->head = list->node->next;
			list->node->prev = NULL;
			free(list->node);
			list->node = list->head;
		}
		free(list->node);
	}
}
