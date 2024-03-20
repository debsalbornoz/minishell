/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:25:59 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/20 15:03:51 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// t_list	*is_argument(t_list *lst_tokens)
// {
// 	lst_tokens->node = lst_tokens->head;
// 	if (lst_tokens->node)
// 	{
// 		while (lst_tokens->node != NULL)
// 		{
// 			if (lst_tokens->node->data->token->type == WORD
// 				&& lst_tokens->node->data->token->type != COMMAND)
// 				lst_tokens->node->data->token->type = ARGUMENT;
// 			lst_tokens->node = lst_tokens->node->next;
// 		}
// 	}
// 	lst_tokens->node = lst_tokens->head;
// 	return (lst_tokens);
// }

t_node	*is_argument(t_node *node)
{
	if (node->data->token->type == WORD && node->data->token->type != COMMAND)
		node->data->token->type = ARGUMENT;
	return (node);
}
