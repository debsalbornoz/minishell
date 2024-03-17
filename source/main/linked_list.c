/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:51:10 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/17 15:01:58 by jraupp           ###   ########.fr       */
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
		while (list->node->next)
			list->node = list->node->next;
		list->node->next = ft_calloc (1, sizeof(t_node));
		list->node = list->node->next;
	}
	return (list);
}

void	print_list(t_list *tokens, void (f)(t_node *))
{
	if (tokens->node)
	{
		tokens->node = tokens->head;
		while (tokens->node && tokens->node->next)
		{
			f(tokens->node);
			tokens->node = tokens->node->next;
		}
		f(tokens->node);
	}
}

void	free_list(t_list *list, void (f)(t_list *))
{
	if (list->node)
	{
		list->node = list->head;
		while (list->node->next)
		{
			list->head = list->node->next;
			f(list);
			list->node = list->head;
		}
		f(list);
	}
}

void	free_tokens(t_list *tokens)
{
	free(tokens->node->data);
	free(tokens->node->value);
}

void	free_env_list(t_list *env_list)
{
	free(env_list->node->data->name);
	if (*env_list->node->value)
		free(env_list->node->value);
}
