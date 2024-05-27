/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/27 16:19:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		printf("\npath : %s\n", aux->data->execution->path);
		aux = aux->next;
	}
}

int	validate_command(t_node *exec)
{
	if (exec->data->execution->path != NULL
		&& exec->data->execution->command_table != NULL
		&& exec->data->execution->envp != NULL)
		return (1);
	return (0);
}
