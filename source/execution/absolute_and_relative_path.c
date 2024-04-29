/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_and_relative_path.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:16:14 by codespace         #+#    #+#             */
/*   Updated: 2024/04/29 12:17:30 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list *is_path(t_list *lst_tokens)
{
	t_node	*aux;

	aux = lst_tokens->head;

	while (aux)
	{
		if (aux->data->tokens->type == COMMAND)
		{
			if (!ft_strncmp(aux->data->tokens->value, "\\", 1) || !ft_strncmp(aux->data->tokens->value, ".\\", 2))
				aux->data->tokens->type = PATH;
		}
		if (aux->data->tokens->type == PIPE)

		aux = aux->next;
	}
}
