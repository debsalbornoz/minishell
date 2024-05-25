/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/24 12:14:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	validate_command(t_node *exec);

int	is_simple_command(t_list *tokens)
{
	t_node	*aux;

	aux = tokens->head;
	while (aux != NULL)
	{
		if (aux->data->token->type == PIPE)
			return (0);
		aux = aux->next;
	}
	aux = tokens->head;
	return (1);
}

int	execute_simple_command(t_list *exec)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!exec)
		return (1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		handle_redirect(exec->node);
		printf("teste\n");
		if (validate_command(exec->node))
			execve(exec->node->data->execution->path,
				exec->node->data->execution->command_table,
				exec->node->data->execution->envp);
		exit(2);
		//finish_process(exec,tokens, envp);
	}
	else
		wait(&status);
	return (status);
}

int	validate_command(t_node *exec)
{
	if (exec->data->execution->path != NULL
		&& exec->data->execution->command_table != NULL
		&& exec->data->execution->envp != NULL)
		return (1);
	return (0);
}
