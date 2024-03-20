/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:23:30 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/20 15:42:11 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*is_command_part1(t_node *head)
{
	if (head->data->token->type == WORD)
		head->data->token->type = COMMAND;
	return (head);
}

t_node	*is_command_part2(t_node *node)
{
	if (node->data->token->type == PIPE)
		if (node->next && !is_redirect_or_pipe(node->next->data->token->type))
			node->next->data->token->type = COMMAND;
	return (node);
}
