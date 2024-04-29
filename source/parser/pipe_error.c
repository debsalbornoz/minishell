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

	flag = 0;
	if (!lst_tokens)
		return (0);
	if (lst_tokens->head->data->token->type == PIPE)
		flag = 1;
	while (lst_tokens->node)
	{
		if (lst_tokens->node->next == NULL
			&& lst_tokens->node->data->token->type == PIPE)
			flag = 1;
		lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (flag);
}

int	check_last_pipe(t_list	*lst_tokens)
{
	int	flag;

	flag = 0;
	if (!lst_tokens)
		return (0);
	while (lst_tokens->node)
	{
		if (lst_tokens->node->next == NULL
			&& lst_tokens->node->data->token->type == PIPE)
			flag = 1;
		lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (flag);
}

int	check_pipe_after_redirect(t_list	*lst_tokens)
{
	int	flag;

	flag = 0;
	if (!lst_tokens)
		return (0);
	while (lst_tokens->node)
	{
		if (find_redirect(lst_tokens->node->data->token->type))
		{
			if (lst_tokens->node->next
				&& lst_tokens->node->next->data->token->type == PIPE)
				flag = 1;
		}
		lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (flag);
}
