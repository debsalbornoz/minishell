/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/06 17:16:04 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_simple_command(t_list *lst_tokens)
{
	lst_tokens->node = lst_tokens->head;
	while (lst_tokens->node)
	{
		if (is_redirect_or_pipe(lst_tokens->node->data->token->type))
			return (0);
		lst_tokens->node = lst_tokens->node->next;
	}
	lst_tokens->node = lst_tokens->head;
	return (1);
}

int	execute_simple_command(t_list *lst_exec)
{
	pid_t	pid;
	int	status;

	(void)lst_exec;

	pid = fork();

	if (pid == -1)
		return -1;
	else if (pid == 0)
		execve(lst_exec->node->data->execution->path, lst_exec->node->data->execution->command_table, lst_exec->node->data->execution->envp);
	else
		wait(&status);
	return status;
}
