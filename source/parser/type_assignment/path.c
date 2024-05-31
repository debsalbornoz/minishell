/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:16:14 by codespace         #+#    #+#             */
/*   Updated: 2024/05/20 12:13:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_node	*is_path(t_node *node)
{
	if (node->data->token->type == WORD)
	{
		if (!ft_strncmp(node->data->token->value, "/", 1)
			|| !ft_strncmp(node->data->token->value, "./", 2))
			node->data->token->type = PATH;
	}
	if (node->data->token->type == PIPE)
	{
		if (node->next && (!ft_strncmp(node->data->token->value, "/", 1)
				|| !ft_strncmp(node->data->token->value, "./", 2)))
			node->next->data->token->type = PATH;
	}
	return (node);
}
