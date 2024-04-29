/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:07:45 by codespace         #+#    #+#             */
/*   Updated: 2024/04/29 12:44:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int set_flag(t_node *node)
{
	int flag;

	flag = 0;
	if (node->data->token->type == OUTPUT)
		flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	if (node->data->token->type == APPEND)
		flag = flag | O_WRONLY | O_CREAT | O_APPEND;
	if (node->data->token->type == HEREDOC || node->data->token->type == INPUT)
		flag = flag | O_RDONLY;
	return (flag);
}

int open_file(t_list *lst_tokens)
{
	int		fd;
	t_node *aux;

	aux = lst_tokens->head;
	while(aux)
	{
		if(find_redirect(aux->data->token->type))
				fd = open(aux->next->data->token->value, set_flag(aux), 0644);
		aux = aux->next;
	}
	return (fd);
}
