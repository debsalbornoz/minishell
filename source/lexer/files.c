/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:23:32 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/16 18:56:05 by dlamark-         ###   ########.fr       */
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
			if (tokens->node->type == INPUT)
			{
				if (tokens->node->next)
					tokens->node->next->type = INPUT_FILE;
			}
			if (tokens->node->type == OUTPUT)
			{
				if (tokens->node->next)
					tokens->node->next->type = OUTPUT_FILE;
			}
			if (tokens->node->type == APPEND)
			{
				if (tokens->node->next)
					tokens->node->next->type = APPEND_FILE;
			}
			tokens->node = tokens->node->next;
		}
		tokens->node = tokens->head;
	}
	return (tokens);
}
