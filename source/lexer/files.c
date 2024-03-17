/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:23:32 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/17 12:49:26 by jraupp           ###   ########.fr       */
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
				if (tokens->node->next)
					tokens->node->next->data->type = INPUT_FILE;
			}
			if (tokens->node->data->type == OUTPUT)
			{
				if (tokens->node->next)
					tokens->node->next->data->type = OUTPUT_FILE;
			}
			if (tokens->node->data->type == APPEND)
			{
				if (tokens->node->next)
					tokens->node->next->data->type = APPEND_FILE;
			}
			tokens->node = tokens->node->next;
		}
		tokens->node = tokens->head;
	}
	return (tokens);
}

t_list	*is_heredoc_key(t_list *tokens)
{
	tokens->node = tokens->head;
	if (tokens->node)
	{
		while (tokens->node != NULL)
		{
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
