/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:59:33 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/01 16:44:41 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <string.h>

void	get_index(t_list *exec);

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

void	save_redirects_and_files(t_list *exec, t_list *tokens)
{
	char	**redir_and_files;

	redir_and_files = NULL;
	while (exec->node)
	{
		redir_and_files = allocate_redir_and_files(tokens->node);
		if (!redir_and_files)
			return ;
		redir_and_files = get_redirects_and_files(&tokens->node,
				redir_and_files);
		exec->node->data->exec->redir_and_files = redir_and_files;
		exec->node = exec->node->next;
	}
	tokens->node = tokens->head;
	exec->node = exec->head;
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
	}
}
