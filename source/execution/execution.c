/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/24 16:21:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_matrix(char **matrix);
void	print_lst_exec(t_list *lst_exec);

t_list	*execute(t_list *lst_tokens, t_list *lst_exec, t_list *lst_env)
{
	lst_exec = create_lst_exec(lst_tokens, lst_exec, lst_env);
	if (!lst_exec)
		return (NULL);
	print_lst_exec(lst_exec);
	if (is_simple_command(lst_tokens))
		execute_simple_command(lst_exec);
	if (lst_exec->node)
		lst_exec->node = lst_exec->head;
	return (lst_exec);
}

void	print_lst_exec(t_list *lst_exec)
{
	t_node	*aux;

	aux = lst_exec->head;
	while (aux)
	{
		printf("command_table : ");
		print_matrix(aux->data->execution->command_table);
		printf("\n redirects and files:");
		print_matrix(aux->data->execution->redirects_and_files);
		printf("\npath : %s\n" , aux->data->execution->path);
		aux = aux->next;
	}
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

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		printf("%s , ", matrix[i]);
		i++;
	}
}
