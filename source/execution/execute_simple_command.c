/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/16 19:34:20 by dlamark-         ###   ########.fr       */
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

int	execute_simple_command(t_list *exec)
{
	pid_t	pid;
	int		status;

	(void)exec;
	pid = fork();
	status = 0;
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		execve(exec->node->data->execution->path,
			exec->node->data->execution->command_table,
			exec->node->data->execution->envp);
	else
		wait(&status);
	return (status);
}
