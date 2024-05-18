/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/18 15:58:56 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	execute_simple_command(t_list *exec, t_list *tokens)
{
	pid_t	pid;
	int		status;
	int		fd_in;
	int		fd_out;

	status = 0;
	fd_in = 0;
	fd_out = 1;
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	tokens = handle_redirect(tokens);
	if (!exec->node)
	{
		dup2(fd_in, 0);
		dup2(fd_out, 1);
		return (1);
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (exec->node->data->execution->path != NULL && exec->node->data->execution->command_table != NULL && exec->node->data->execution->envp != NULL)
		{
			printf("Teste");
			execve(exec->node->data->execution->path,
				exec->node->data->execution->command_table,
				exec->node->data->execution->envp);
		}
	}
	else
	{
		wait(&status);
		dup2(fd_in, 0);
		dup2(fd_out, 1);
	}
	return (status);
}
