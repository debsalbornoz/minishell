/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_assignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:26:00 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/12 21:57:31 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	is_command(t_list *tokens)
{
	tokens->node = tokens->head;
	if (tokens->node)
	{
		while (tokens->node != NULL)
		{
			if (tokens->head->type == WORD)
				tokens->head->type = COMMAND;
			if (tokens->node->type == PIPE)
				if (tokens->node->next)
					tokens->node->next->type = COMMAND;
			tokens->node = tokens->node->next;
		}
	}
}

// void	is_argument(t_list *tokens)
// {
// 	tokens->node = tokens->head;
// 	while (tokens->node != NULL)
// 	{
// 		if (tokens->node->type == COMMAND)
// 		{
// 			if (tokens->node->type)
// 			{
// 				while (tokens->node->next->type != PIPE
// 					&& tokens->node->next->type != REDIRECT
// 					&& tokens->node->next != NULL)
// 				{
// 						tokens->node->next->type = ARGUMENT;
// 						tokens->node = tokens->node->next;
// 				}
// 			}
// 		}
// 		tokens->node = tokens->node->next;
// 	}
// }

void	type_assignment(t_list *tokens)
{
	is_command(tokens);
	// is_argument(tokens);
}
