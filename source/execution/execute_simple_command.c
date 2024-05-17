/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/17 19:41:01 by codespace        ###   ########.fr       */
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

int	execute_simple_command(t_list *exec, t_list *tokens, t_list *envp)
{
	pid_t	pid;
	int		status;
	int		fd_in;
	int		fd_out;

	fd_in = 0;
	fd_out = 1;
	(void)exec;
	(void)envp;
	pid = fork();
	status = 0;
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		fd_in = dup(STDIN_FILENO);
		fd_out = dup(STDOUT_FILENO);
		tokens = handle_redirect(tokens);
		pid = fork();
		if (pid == 0)
		{
			execve(exec->node->data->execution->path,
				exec->node->data->execution->command_table,
				exec->node->data->execution->envp);
		}
		else
		{
			wait(&status);
			dup2(fd_in, 0);
			dup2(fd_out, 1);
		}
	}
	else
		wait(&status);
	return (status);
}
