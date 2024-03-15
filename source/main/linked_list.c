/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:51:10 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/12 21:46:37 by dlamark-         ###   ########.fr       */
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
	list->node->value = ft_strdup(value);
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
			printf("%i\n", list->node->type);
			list->node = list->node->next;
		}
		printf("%s\n", list->node->value);
	}
}

/*void	free_list(t_list *list)
{
	if (list->node)
	{
		list->node = list->head;
		while (list->node && list->node->next)
		{
			list->head = list->node->next;
			list->node->prev = NULL;
			free(list->node->value);
			free(list->node);
			list->node = list->head;
		}
		free(list->node->value);
		free(list->node);
	}
}
*/

void free_list(t_list *list)
{
	t_node_token *next_node;
    if (list)
	{
        while (list->node) 
		{
            next_node = list->node->next;
            if (list->node->value)
                free(list->node->value);
            free(list->node); 
            list->node = next_node;
        }
        list->head = NULL;
        list->node = NULL;
    }
}