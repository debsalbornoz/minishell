/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:51:10 by jraupp            #+#    #+#             */
/*   Updated: 2024/07/28 17:25:21 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*add_node(t_list *list)
{
	if (!list->node)
	{
		list->node = ft_calloc (1, sizeof(t_node));
		list->head = list->node;
	}
	else
	{
		list->node->next = ft_calloc (1, sizeof(t_node));
		list->node = list->node->next;
	}
	return (list);
}

t_list	*runs_on_list(t_list *list, t_node *(f)(t_node *))
{
	list->node = list->head;
	if (list->node)
	{
		list->node = list->head;
		while (list->node && list->node->next)
		{
			list->node = f(list->node);
			list->node = list->node->next;
		}
		list->node = f(list->node);
	}
	return (list);
}

int	count_nodes(t_list *lst)
{
	int		i;
	t_node	*aux;

	i = 0;
	aux = lst->head;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}
