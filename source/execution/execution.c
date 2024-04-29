/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/29 14:25:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*execution(t_list *lst_tokens, t_list *lst_exec,
	t_list *lst_env)
{
	lst_tokens = handle_redirect(lst_tokens, lst_exec);
	lst_exec = prepare_for_execution(lst_tokens, lst_exec, lst_env);
	if (lst_exec->node->data->execution ->path != NULL)
		execute_simple_command(lst_exec);
	return (lst_exec);
}

int	find_builtin(t_list *lst_tokens)
{
	t_node	*aux;

	aux = lst_tokens->head;
	while(aux)
	{
		if(aux->data->token->type == BUILTIN)
			return (1);
		aux = aux->next;
	}
	return (0);
}
t_list *prepare_for_execution(t_list *lst_tokens, t_list *lst_exec,
	t_list *lst_env)
{
	lst_exec = add_node(lst_exec);
	lst_exec->node->data = ft_calloc(1, sizeof(union u_data));
	if (!lst_exec->node->data)
		return (NULL);
	lst_exec->node->data->execution = ft_calloc(1, sizeof(t_exec));
	if (!lst_exec->node->data->execution)
		return (NULL);
	lst_exec->node->data->execution->envp = env_list_to_str_array(lst_env);
	lst_exec->node->data->execution->command_table = create_command_table
		(lst_tokens, lst_exec);
	lst_exec->node->data->execution
		->path = save_path(lst_exec, lst_tokens, lst_env);
	lst_exec->node = lst_exec->head;
	lst_tokens->node = lst_tokens->head;
	return (lst_exec);
}
