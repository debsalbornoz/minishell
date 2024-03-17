/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:25:59 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/17 15:37:21 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*is_argument(t_list *tokens)
{
	tokens->node = tokens->head;
	if (tokens->node)
	{
		while (tokens->node != NULL)
		{
			if (tokens->node->data->type == WORD
				&& tokens->node->data->type != COMMAND)
				tokens->node->data->type = ARGUMENT;
			tokens->node = tokens->node->next;
		}
	}
	tokens->node = tokens->head;
	return (tokens);
}
