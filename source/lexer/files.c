/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:23:32 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/17 15:17:09 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*is_file(t_list *tokens)
{
	tokens->node = tokens->head;
	if (tokens->node)
	{
		while (tokens->node != NULL)
		{
			if (tokens->node->data->type == INPUT)
			{
				if (tokens->node->next
					&& !is_redirect_or_pipe(tokens->node->next->data->type))
					tokens->node->next->data->type = INPUT_FILE;
			}
			if (tokens->node->data->type == OUTPUT
				&& !is_redirect_or_pipe(tokens->node->next->data->type))
			{
				if (tokens->node->next)
					tokens->node->next->data->type = OUTPUT_FILE;
			}
			tokens->node = tokens->node->next;
		}
		tokens->node = tokens->head;
	}
	return (tokens);
}

t_list	*is_append_or_heredoc_key(t_list *tokens)
{
	tokens->node = tokens->head;
	if (tokens->node)
	{
		while (tokens->node != NULL)
		{
			if (tokens->node->data->type == APPEND
				&& !is_redirect_or_pipe(tokens->node->next->data->type))
			{
				if (tokens->node->next)
					tokens->node->next->data->type = APPEND_FILE;
			}
			if (tokens->node->data->type == HEREDOC)
			{
				if (tokens->node->next)
					tokens->node->next->data->type = HEREDOC_KEY;
			}
			tokens->node = tokens->node->next;
		}
		tokens->node = tokens->head;
	}
	return (tokens);
}
