/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:59:33 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/30 20:15:03 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <string.h>

void	get_index(t_list *exec);
t_list	*init_exec_addr(void);

t_list	*init_exec_addr(void)
{
	static t_list	exec;

	exec.node = 0;
	return (&exec);
}

t_list	*create_lst_exec(t_list *tokens, t_list *exec, t_list *envp)
{
	exec = init_exec_addr();
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
	exec->node = exec->head;
	return (exec);
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

void	find_path(t_list *tokens, t_list *exec, t_list *envp)
{
	char		*path;

	envp->node = envp->head;
	path = NULL;
	if (!exec || !tokens || !envp)
		return ;
	while (exec->node)
	{
		if (exec->node->data->execution->command_table)
		{
			path = validate_path(exec->node->data->execution->command_table,
					exec->node, envp);
			exec->node->data->execution->path = ft_strdup(path);
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
		exec->node->data->execution->redirects_and_files = redir_and_files;
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
		aux->data->execution->index = i;
		aux = aux->next;
	}
}
int	create_heredocs(t_node	*exec)
{
	t_node	*aux;
	int		i;
	char	*filename;
	int		j;

	i = 0;
	j = 0;
	aux = exec;
	filename = NULL;
	aux->data->execution->eofs = allocate_eof(exec);
	if (!exec->data->execution->redirects_and_files)
		return (1);
	while (aux)
	{
		j = 0;
		i = 0;
		while (aux->data->execution->redirects_and_files[i])
		{
			printf("teste\n");
			if (ft_strncmp("<<", aux->data->execution->redirects_and_files[i], 2) == 0)
			{
				printf("?");
				if (aux->data->execution->redirects_and_files[i + 1])
				{
					aux->data->execution->eofs[j] = ft_strdup(aux->data->execution->redirects_and_files[i + 1]);
					filename = handle_heredoc(aux,i,j);
					free(aux->data->execution->redirects_and_files[i + 1]);
					aux->data->execution->redirects_and_files[i + 1] = filename;
					j++;
				}
			}
			i++;
		}
		aux = aux->next;
	}
	return (0);
}
