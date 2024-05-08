/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_and_arguments.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:25:59 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/06 16:48:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

t_node	*is_argument(t_node *node)
{
	if (node->data->token->type == WORD
		&& node->data->token->type != COMMAND
		&& node->data->token->type != PATH)
		node->data->token->type = ARGUMENT;
	return (node);
}
