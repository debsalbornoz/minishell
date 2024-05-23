/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/23 13:02:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*execute(t_list *lst_tokens, t_list *lst_exec, t_list *lst_env)
{
	lst_exec = create_lst_exec(lst_tokens, lst_exec, lst_env);
	if (!lst_exec)
		return (NULL);
	lst_exec->node = lst_exec->head;
	if (is_simple_command(lst_tokens))
		execute_simple_command(lst_exec, lst_tokens);
	if (lst_exec->node)
		lst_exec->node = lst_exec->head;
	return (lst_exec);
}

t_list	*allocate_lst_exec(t_list *tokens, t_list *exec, t_list *envp)
{
	t_node	*aux;

	aux = tokens->head;
	if (aux)
	{
		exec = add_node(exec);
		exec->node->data = ft_calloc(1, sizeof(union u_data));
		exec->node->data->execution = ft_calloc(1, sizeof(t_exec));
		exec->node->data->execution->envp = env_list_to_str_array(envp);
	}
	while (aux)
	{
		if (aux->data->token->type == PIPE)
		{
			exec = add_node(exec);
			exec->node->data = ft_calloc(1, sizeof(union u_data));
			exec->node->data->execution = ft_calloc(1, sizeof(t_exec));
			exec->node->data->execution->envp = env_list_to_str_array(envp);
		}
		aux = aux->next;
	}
	return (exec);
}

t_list	*create_lst_exec(t_list *tokens, t_list *exec, t_list *envp)
{
	exec = allocate_lst_exec(tokens, exec, envp);
	if (exec->node)
	{
		create_command_table(tokens, exec);
		if (exec->node->data->execution->command_table != NULL)
			fill_path_in_exec(tokens, exec, envp);
		fill_redir_and_files(exec, tokens);
		exec->node = exec->head;
		envp->node = envp->head;
	}
	return (exec);
}
