/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:23:30 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/24 14:31:49 by codespace        ###   ########.fr       */
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
t_node *is_path(t_node *node)
{

		if (node->data->token->type == COMMAND)
		{
			if (!ft_strncmp(node->data->token->value, "/", 1) || !ft_strncmp(node->data->token->value, "./", 2))
				node->data->token->type = PATH;
		}
		if (node->data->token->type == PIPE)
		{
			if(node->next && (!ft_strncmp(node->data->token->value, "/", 1) || !ft_strncmp(node->data->token->value, "./", 2)))
				node->next->data->token->type = PATH;
		}
		return (node);
}
