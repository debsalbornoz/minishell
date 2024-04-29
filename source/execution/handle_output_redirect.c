/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_output_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:25:27 by codespace         #+#    #+#             */
/*   Updated: 2024/04/29 12:21:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_outputs(t_list *lst_tokens)
{
	int i;
	t_node	*aux;

	i = 0;
	aux = lst_tokens->head;
	while (aux)
	{
		if (aux->data->token->type == OUTPUT )
			i++;
		aux =aux->next;
	}
	return (i);
}

t_list *handle_redirect(t_list *lst_tokens, t_list *lst_exec)
{
	(void)lst_exec;

	if(find_redirect(lst_tokens->node->data->token->type))
	{
		open_file(lst_tokens);
	}
	return (lst_exec);
}
int has_command(t_list *lst_tokens)
{
	t_node	*aux;

	aux = lst_tokens->head;
	while (aux)
	{
		if (aux->data->token->type == PATH || aux->data->token->type == COMMAND || aux->data->token->type == BUILTIN)
			return (1);
		aux = aux->next;
	}
	return (0);
}
int has_pipe(t_list *lst_tokens)
{
	t_node	*aux;

	aux = lst_tokens->head;
	while (aux)
	{
		if (aux->data->token->type == PIPE)
			return (1);
		aux = aux->next;
	}
	return (0);
}

int type_redirect(int type)
{
	if (type == APPEND || type == OUTPUT || type == INPUT || type == HEREDOC)
		return (1);
	return (0);
}
