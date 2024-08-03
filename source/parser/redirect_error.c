/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:56:46 by dlamark-          #+#    #+#             */
/*   Updated: 2024/08/03 19:01:18 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_redirect(int type)
{
	return (type == INPUT || type == HEREDOC
		|| type == OUTPUT || type == APPEND);
}

int	redirect_error(t_list	*tokens)
{
	int		flag;
	t_node	*aux;

	flag = 0;
	aux = NULL;
	if (!tokens)
		return (0);
	if (tokens)
		aux = tokens->head;
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
	if (redirect_at_end(tokens))
		flag = 1;
	return (flag);
}

int	redirect_at_end(t_list *tokens)
{
	t_node	*aux;

	aux = tokens->head;
	while (aux)
	{
		if (aux->next == NULL && find_redirect(aux->data->token->type))
		{
			printf("chega aqui? \n");
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}
