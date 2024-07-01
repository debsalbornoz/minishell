/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:59:33 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/01 12:35:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_list	*create_lst_exec(t_list *tokens, t_list *exec, t_list *envp)
{
	exec = initialize_lst_exec(tokens, exec, envp);
	if (!exec->node)
		return (NULL);
	create_command_table(tokens, exec);
	find_path(tokens, exec, envp);
	save_redirects_and_files(exec, tokens);
	get_index(exec);
	envp->node = envp->head;
	exec->node = exec->head;
	return (exec);
}

t_list	*initialize_lst_exec(t_list *tokens, t_list *exec, t_list *envp)
{
	t_node	*aux;

	aux = tokens->head;
	if (aux)
	{
		exec = add_node(exec);
		exec->node->data = ft_calloc(1, sizeof(union u_data));
		exec->node->data->exec = ft_calloc(1, sizeof(t_exec));
		exec->node->data->exec->envp = env_list_to_str_array(envp);
	}
	while (aux)
	{
		if (aux->data->token->type == PIPE)
		{
			exec = add_node(exec);
			exec->node->data = ft_calloc(1, sizeof(union u_data));
			exec->node->data->exec = ft_calloc(1, sizeof(t_exec));
			exec->node->data->exec->envp = env_list_to_str_array(envp);
		}
		aux = aux->next;
	}
	exec->node = exec->head;
	return (exec);
}

void	get_index(t_list *exec)
{
	t_node	*aux;
	int		i;

	aux = exec->head;
	i = 0;
	while (aux)
	{
		aux->data->exec->index = i;
		aux = aux->next;
		i++;
	}
}
