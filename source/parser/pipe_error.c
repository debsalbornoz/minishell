/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:56:20 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/07 17:37:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_error(t_list	*tokens)
{
	if (check_first_and_last_pipe(tokens) || check_pipe_after_redirect(tokens))
		return (1);
	return (0);
}

int	check_first_and_last_pipe(t_list	*tokens)
{
	int		flag;
	t_node	*aux;

	flag = 0;
	if (!tokens)
		return (0);
	aux = tokens->head;
	if (tokens->head->data->token->type == PIPE)
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

int	check_pipe_after_redirect(t_list	*tokens)
{
	int		flag;
	t_node	*aux;

	flag = 0;
	if (!tokens)
		return (0);
	aux = tokens->head;
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
