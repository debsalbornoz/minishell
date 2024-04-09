/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:56:46 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/06 14:12:22 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_redirect(int type)
{
	return (type == INPUT || type == HEREDOC
		|| type == OUTPUT || type == APPEND);
}

int	output_error(t_list	*lst_tokens)
{
	int	flag;

	flag = 0;
	if (!lst_tokens)
		return (0);
	if (lst_tokens)
		lst_tokens->node = lst_tokens->head;
	while (lst_tokens->node)
	{
		if (lst_tokens->node->data->token->type == OUTPUT)
		{
			if (lst_tokens->node->next)
			{
				if (find_redirect(lst_tokens->node->next->data->token->type))
					flag = 1;
			}
		}
			lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (flag);
}

int	input_error(t_list	*lst_tokens)
{
	int	flag;

	flag = 0;
	if(!lst_tokens)
		return (0);
	if (lst_tokens)
		lst_tokens->node = lst_tokens->head;
	while (lst_tokens->node)
	{
		if (lst_tokens->node->data->token->type == INPUT)
		{
			if (lst_tokens->node->next)
			{
				if (find_redirect(lst_tokens->node->next->data->token->type))
					flag = 1;
			}
		}
			lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (flag);
}

int	append_error(t_list	*lst_tokens)
{
	int	flag;

	flag = 0;
	if(!lst_tokens)
		return (0);
	if (lst_tokens)
		lst_tokens->node = lst_tokens->head;
	while (lst_tokens->node)
	{
		if (lst_tokens->node->data->token->type == APPEND)
		{
			if (lst_tokens->node->next)
			{
				if (find_redirect(lst_tokens->node->next->data->token->type))
					flag = 1;
			}
		}
			lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (flag);
}

int	heredoc_error(t_list	*lst_tokens)
{
	int	flag;

	flag = 0;
	if(lst_tokens)
		return (0);
	if (lst_tokens)
		lst_tokens->node = lst_tokens->head;
	while (lst_tokens->node)
	{
		if (lst_tokens->node->data->token->type == HEREDOC)
		{
			if (lst_tokens->node->next)
			{
				if (find_redirect(lst_tokens->node->next->data->token->type))
					flag = 1;
			}
		}
			lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (flag);
}
