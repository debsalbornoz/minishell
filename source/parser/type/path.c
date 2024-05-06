/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:16:14 by codespace         #+#    #+#             */
/*   Updated: 2024/05/05 22:42:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_list *find_path(t_list *lst_tokens)
{
	t_node	*aux;

	aux = lst_tokens->head;

	while (aux)
	{
		if (aux->data->token->type == COMMAND)
		{
			if (!ft_strncmp(aux->data->token->value, "\\", 1) || !ft_strncmp(aux->data->token->value, ".\\", 2))
				aux->data->token->type = PATH;
		}
		if (aux->data->token->type == PIPE)

		aux = aux->next;
	}
	return(lst_tokens);
}
