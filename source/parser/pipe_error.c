/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:56:20 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/29 12:39:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_first_pipe(t_list	*lst_tokens)
{
	int	flag;
	t_node	*aux;

	flag = 0;
	if (!lst_tokens)
		return (0);
	aux = lst_tokens->head;
	if (lst_tokens->head->data->token->type == PIPE)
		flag = 1;
	while (aux)
	{
		if (aux->next == NULL
			&& aux->data->token->type == PIPE)
			flag = 1;
		aux = aux->next;
	}
	return (flag);
}

int	check_last_pipe(t_list	*lst_tokens)
{
	int	flag;
	t_node	*aux;

	flag = 0;
	if (!lst_tokens)
		return (0);
	aux = lst_tokens->head;
	while (aux)
	{
		if (aux->next == NULL
			&& aux->data->token->type == PIPE)
			flag = 1;
		aux = aux->next;
	}
	return (flag);
}

int	check_pipe_after_redirect(t_list	*lst_tokens)
{
	int	flag;
	t_node	*aux;

	flag = 0;
	if (!lst_tokens)
		return (0);
	aux = lst_tokens->head;
	while (aux)
	{
		if (find_redirect(aux->data->token->type))
		{
			if (aux->next
				&& aux->next->data->token->type == PIPE)
				flag = 1;
		}
		aux = aux->next;
	}
	return (flag);
}
