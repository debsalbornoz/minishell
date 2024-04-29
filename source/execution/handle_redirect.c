/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:07:45 by codespace         #+#    #+#             */
/*   Updated: 2024/04/29 12:21:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int return_flag(t_node *node)
{
	int flag;

	flag = 0;
	if (node->data->token->type == OUTPUT)
		flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	else if (node->data->token->type == APPEND)
		flag = flag | O_WRONLY | O_CREAT | O_APPEND;
	return (flag);
}

int open_file(t_list *lst_tokens)
{
	int		fd;
	int		flag;
	t_node	*aux;

	aux = lst_tokens->head;
	while(aux)
	{
		if(aux->data->token->type == OUTPUT)
		{
			if (aux->next)
			{
				flag = return_flag(aux);
				fd = open(aux->next->data->token->value, flag, 0644);
			}
		}
		aux = aux->next;
	}
	return (fd);
}
