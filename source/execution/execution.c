/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/25 12:03:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*create_execution_list(t_list *lst_tokens, t_list *lst_exec,
	t_list *lst_env)
{
	if (is_simple_command(lst_tokens) && !find_builtin(lst_tokens))
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
		if (lst_exec->node->data->execution
			->path != NULL)
		{
			execute_simple_command(lst_exec);
		}
	}
	return (lst_exec);
}

int	find_builtin(t_list *lst_tokens)
{
	lst_tokens->node = lst_tokens->head;
	while(lst_tokens->node)
	{
		if(lst_tokens->node->data->token->type == BUILTIN)
			return (1);
		lst_tokens->node = lst_tokens->node->next;
	}
	return (0);
}
