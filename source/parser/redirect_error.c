/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:56:46 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/07 17:12:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_redirect(int type)
{
	return (type == INPUT || type == HEREDOC
		|| type == OUTPUT || type == APPEND);
}

int	redirect_error(t_list	*lst_tokens)
{
	int	flag;
	t_node *aux;

	flag = 0;
	if (!lst_tokens)
		return (0);
	if (lst_tokens)
		aux = lst_tokens->head;
	while (aux)
	{
		if (find_redirect(aux->data->token->type))
		{
			if (aux->next)
			{
				if (find_redirect(aux->next->data->token->type))
					flag = 1;
			}
		}
		aux = aux->next;
	}
	aux = lst_tokens->head;
	return (flag);
}
