/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:46:41 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/30 13:01:30 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_first_pipe(t_list	*lst_tokens)
{
	int	flag;

	flag = 0;
	if (lst_tokens)
	{
		if (lst_tokens->head->data->token->type == PIPE)
			flag = 1;
		while (lst_tokens->node)
		{
			if (lst_tokens->node->next == NULL
				&& lst_tokens->node->data->token->type == PIPE)
				flag = 1;
			lst_tokens->node = lst_tokens->node->next;
		}
	}
	lst_tokens->node = lst_tokens->head;
	return (flag);
}

int	check_last_pipe(t_list	*lst_tokens)
{
	int	flag;

	flag = 0;
	if (lst_tokens)
	{
		while (lst_tokens->node)
		{
			if (lst_tokens->node->next == NULL
				&& lst_tokens->node->data->token->type == PIPE)
				flag = 1;
			lst_tokens->node = lst_tokens->node->next;
		}
	}
	lst_tokens->node = lst_tokens->head;
	return (flag);
}

int	check_redirect_after_pipe(t_list	*lst_tokens)
{
	int	flag;

	flag = 0;
	if (lst_tokens)
	{
		while (lst_tokens->node)
		{
			if (lst_tokens->node->data->token->type == PIPE)
			{
				if (lst_tokens->node->next
					&& find_redirect(lst_tokens->node->next->data->token->type))
					flag = 1;
			}
			lst_tokens->node = lst_tokens->node->next;
		}
		lst_tokens->node = lst_tokens->head;
	}
	return (flag);
}
