/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:56:46 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/25 17:18:25 by codespace        ###   ########.fr       */
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
	t_node *aux;

	flag = 0;
	if (!lst_tokens)
		return (0);
	if (lst_tokens)
		aux = lst_tokens->head;
	while (aux)
	{
		if (aux->data->token->type == OUTPUT)
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

int	input_error(t_list	*lst_tokens)
{
	int	flag;
	t_node	*aux;

	flag = 0;
	if (!lst_tokens)
		return (0);
	if (lst_tokens)
		aux = lst_tokens->head;
	while (aux)
	{
		if (aux->data->token->type == INPUT)
		{
			if (aux->next)
			{
				if (find_redirect(aux->next->data->token->type))
					flag = 1;
			}
		}
		aux = aux->next;
	}
	return (flag);
}

int	append_error(t_list	*lst_tokens)
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
		if (aux->data->token->type == APPEND)
		{
			if (aux->next)
			{
				if (find_redirect(aux->next->data->token->type))
					flag = 1;
			}
		}
		aux = aux->next;
	}
	return (flag);
}

int	heredoc_error(t_list	*lst_tokens)
{
	int	flag;
	t_node *aux;

	flag = 0;
	if (lst_tokens)
		return (0);
	if (lst_tokens)
		aux = lst_tokens->head;
	while (aux)
	{
		if (aux->data->token->type == HEREDOC)
		{
			if (aux->next)
			{
				if (find_redirect(aux->next->data->token->type))
					flag = 1;
			}
		}
		aux = aux->next;
	}
	return (flag);
}
int redirect_at_end(t_list *lst_tokens)
{
	t_node	*aux;

	aux = lst_tokens->head;

	while (aux)
	{
		if (aux->next == NULL && find_redirect(aux->data->token->type))
			return (1);
		aux = aux->next;
	}
	return (0);
}
