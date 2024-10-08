/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:59:33 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/20 14:51:24 by dlamark-         ###   ########.fr       */
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
	create_multi_redir_table(tokens, exec);
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

void	create_multi_redir_table(t_list *tokens, t_list *exec)
{
	allocate_multi_redir_table(exec->head, tokens->node, 0);
	fill_redir_and_files(tokens, exec);
	tokens->node = tokens->head;
	exec->node = exec->head;
}

void	create_command_table(t_list *tokens, t_list *exec)
{
	if (is_simple_command(tokens) && exec)
		create_simple_cmd_table(tokens, exec);
	else
		create_multi_cmd_table(tokens, exec);
	tokens->node = tokens->head;
	exec->node = exec->head;
}
