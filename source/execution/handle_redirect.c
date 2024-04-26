/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:07:45 by codespace         #+#    #+#             */
/*   Updated: 2024/04/26 17:39:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int return_flag(t_node *node)
{
	int flag;

	flag = 0;
	if (node->data->token->type == OUTPUT)
		flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	return (flag);
}

int open_file(t_list *lst_tokens)
{
	int		fd;
	int		flag;

	lst_tokens->node = lst_tokens->head;
	while(lst_tokens->node)
	{
		if(lst_tokens->node->data->token->type == OUTPUT)
		{
			if (lst_tokens->node->next)
			{
				flag = return_flag(lst_tokens->node);
				fd = open(lst_tokens->node->next->data->token->value, flag, 0644);
			}
		}
		lst_tokens->node = lst_tokens->node->next;
	}
	return (fd);
}
