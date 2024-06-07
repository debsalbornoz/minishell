/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/07 14:36:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void	print_matrix(char **matrix);
void	print_exec_node(t_list *exec);

t_list	*execute(t_list *lst_tokens, t_list *lst_exec,
	t_list *lst_env, char *input)
{
	lst_exec = create_lst_exec(lst_tokens, lst_exec, lst_env);
	if (!lst_exec)
		return (NULL);
	if (is_simple_command(lst_tokens))
		execute_simple_command(lst_exec, lst_tokens, lst_env, input);
	close_fds();
	if (lst_exec->node)
		lst_exec->node = lst_exec->head;
	return (lst_exec);
}
void	print_exec_node(t_list *exec)
{
	t_node	*exec_node;

	exec_node = exec->head;
	while (exec_node)
	{
		printf("command table : ");
		print_matrix(exec_node->data->exec->command_table);
		printf("\n");
		printf("redirects and files: ");
		print_matrix(exec_node->data->exec->redir_and_files);
		printf("\n");
		exec_node = exec_node->next;
	}
}

void	print_matrix(char **matrix)
{
	int i = 0;
	while (matrix[i] != NULL)
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}
