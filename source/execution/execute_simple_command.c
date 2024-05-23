/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/23 18:38:38 by codespace        ###   ########.fr       */
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

	(void)tokens;
	status = 0;
	if (!exec)
		return (1);
	handle_redirect(exec->node);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		printf("teste\n");
		if (exec->node->data->execution->path != NULL
			&& exec->node->data->execution->command_table != NULL
			&& exec->node->data->execution->envp != NULL)
			execve(exec->node->data->execution->path,
				exec->node->data->execution->command_table,
				exec->node->data->execution->envp);
		printf("porque n executou?\n");
	}
	else
		wait(&status);
	return (status);
}
