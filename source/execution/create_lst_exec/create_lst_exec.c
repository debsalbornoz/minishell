/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:59:33 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/01 18:28:37 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <string.h>

t_list	*create_lst_exec(t_list *tokens, t_list *exec, t_list *envp)
{
	exec = initialize_lst_exec(tokens, exec, envp);
	if (exec->node)
	{
		create_command_table(tokens, exec);
		find_path(tokens, exec, envp);
		save_redirects_and_files(exec, tokens);
		get_index(exec);
	}
	envp->node = envp->head;
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

void	find_path(t_list *tokens, t_list *exec, t_list *envp)
{
	char	*path;

	envp->node = envp->head;
	path = NULL;
	if (!exec || !tokens || !envp)
		return ;
	while (exec->node)
	{
		if (exec->node->data->exec->command_table)
		{
			path = validate_path(exec->node->data->exec->command_table,
					exec->node, envp);
			exec->node->data->exec->path = ft_strdup(path);
			free(path);
		}
		exec->node = exec->node->next;
	}
	exec->node = exec->head;
	tokens->node = tokens->head;
}
