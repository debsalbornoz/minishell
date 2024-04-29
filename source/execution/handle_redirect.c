/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:07:45 by codespace         #+#    #+#             */
/*   Updated: 2024/04/29 14:13:16 by codespace        ###   ########.fr       */
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

t_list  *open_file(t_list *lst_tokens)
{
	t_node 	*aux;

	aux = lst_tokens->head;
	while (aux)
	{
		if(find_redirect(aux->data->token->type))
		{
			if (aux->next)
				open(aux->next->data->token->value, set_flag(aux), 0644);
		}
		aux = aux->next;
	}

	return (lst_tokens);
}
t_list *handle_redirect(t_list *lst_tokens, t_list *lst_exec)
{

	(void)lst_exec;
	lst_tokens = open_file(lst_tokens);
	lst_tokens = remove_redirect_and_next(lst_tokens);
	lst_tokens->node = lst_tokens->head;
	return (lst_tokens);
}

t_list *remove_redirect_and_next(t_list *lst_tokens)
{
	t_node *current = lst_tokens->head;
	t_node *next_node = NULL;

	if (!lst_tokens || !lst_tokens->head)
		return (NULL);
	while (current && current->next)
	{
		if (find_redirect(current->data->token->type))
		{
			next_node = current->next;
			if (next_node)
			{
				current->next = next_node->next;
				free(next_node);
			}
			next_node = current->next;
			free(current);
			current = next_node;
			current = lst_tokens->head;
		}
		else
		current = current->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (lst_tokens);
}

