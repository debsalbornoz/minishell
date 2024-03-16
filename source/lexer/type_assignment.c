/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_assignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:26:00 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/16 18:50:55 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*type_assignment(t_list *tokens)
{
	tokens = is_command(tokens);
	tokens = is_builtin(tokens);
	tokens = is_file(tokens);
	return (tokens);
}

// void	is_argument(t_list *tokens)
//{
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
