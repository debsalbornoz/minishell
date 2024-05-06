/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:23:32 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/20 20:40:55 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_node	*is_file(t_node *node)
{
	if (node->next && !is_redirect_or_pipe(node->next->data->token->type))
	{
		if (node->data->token->type == INPUT)
			node->next->data->token->type = INPUT_FILE;
		if (node->data->token->type == OUTPUT)
			node->next->data->token->type = OUTPUT_FILE;
		if (node->data->token->type == APPEND)
			node->next->data->token->type = APPEND_FILE;
	}
	return (node);
}

t_node	*is_heredoc_key(t_node *node)
{
	if (node->next && !is_redirect_or_pipe(node->next->data->token->type))
	{
		if (node->data->token->type == HEREDOC)
			node->next->data->token->type = HEREDOC_KEY;
	}
	return (node);
}
