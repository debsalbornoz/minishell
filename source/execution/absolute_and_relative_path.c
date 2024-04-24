/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_and_relative_path.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:16:14 by codespace         #+#    #+#             */
/*   Updated: 2024/04/24 14:04:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list *is_path(t_list *lst_tokens)
{
	lst_tokens->node = lst_tokens->head;

	while (lst_tokens->node)
	{
		if (lst_tokens->node->data->tokens->type == COMMAND)
		{
			if (!ft_strncmp(lst_tokens->node->data->tokens->value, "\\", 1) || !ft_strncmp(lst_tokens->node->data->tokens->value, ".\\", 2))
				lst_tokens->node->data->tokens->type = PATH;
		}
		if (lst_tokens->node->data->tokens->type == PIPE)

		lst_tokens->node = lst_tokens->node->next;
	}
}
