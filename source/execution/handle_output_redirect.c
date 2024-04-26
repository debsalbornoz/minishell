/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_output_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:25:27 by codespace         #+#    #+#             */
/*   Updated: 2024/04/26 17:38:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_outputs(t_list *lst_tokens)
{
	int i;

	i = 0;
	lst_tokens->node = lst_tokens->head;
	while (lst_tokens->node)
	{
		if (lst_tokens->node->data->token->type == OUTPUT )
			i++;
		lst_tokens->node =lst_tokens->node->next;
	}
	return (i);
}

t_list *handle_single_output(t_list *lst_tokens, t_list *lst_exec)
{
	int output;
	(void)lst_exec;
	output = count_outputs(lst_tokens);
	if(output == 1 && !has_command(lst_tokens) && !has_pipe(lst_tokens))
	{
		open_file(lst_tokens);
	}
	lst_tokens->node = lst_tokens->head;
	return (lst_exec);
}
int has_command(t_list *lst_tokens)
{
	lst_tokens->node = lst_tokens->head;
	while (lst_tokens->node)
	{
		if (lst_tokens->node->data->token->type == PATH || lst_tokens->node->data->token->type == COMMAND || lst_tokens->node->data->token->type == BUILTIN)
			return (1);
		lst_tokens->node = lst_tokens->node->next;
	}
	return (0);
}
int has_pipe(t_list *lst_tokens)
{
	lst_tokens->node = lst_tokens->head;
	while (lst_tokens->node)
	{
		if (lst_tokens->node->data->token->type == PIPE)
			return (1);
		lst_tokens->node = lst_tokens->node->next;
	}
	return (0);
}
