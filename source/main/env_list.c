/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:59:28 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/12 21:13:31 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_list	*init_env_list(t_env_list *list)
{
	list->node = 0;
	list->head = list->node;
	list->tail = list->node;
	return (list);
}

t_env_list	*add_env_node(t_env_list *list, char *name, char *value)
{
	if (!list->node)
	{
		list->node = ft_calloc (1, sizeof(t_node_env));
		list->head = list->node;
	}
	else
	{
		list->node = list->tail;
		list->node->next = ft_calloc (1, sizeof(t_node_env));
		list->node = list->node->next;
	}
	list->tail = list->node;
	list->node->name = ft_strdup(name);
	list->node->value = ft_strdup(value);
	return (list);
}

void	print_env_list(t_env_list *list)
{
	if (list->node)
	{
		list->node = list->head;
		while (list->node && list->node->next)
		{
			printf("%s = %s\n", list->node->name, list->node->value);
			list->node = list->node->next;
		}
		printf("%s\n", list->node->value);
	}
}

void	free_env_list(t_env_list *list)
{
	if (list->node)
	{
		list->node = list->head;
		while (list->node && list->node->next)
		{
			list->head = list->node->next;
			free(list->node->value);
			free(list ->node->name);
			free(list->node);
			list->node = list->head;
		}
		free(list->node->value);
		free(list->node->name);
		free(list->node);
	}
}
