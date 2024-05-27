/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/27 16:19:39 by codespace        ###   ########.fr       */
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

int	execute_simple_command(t_list *exec,
	t_list *tokens, t_list *envp, char *input)
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
		redirect_and_execute(exec, tokens, envp, input);
	else
		wait(&status);
	return (status);
}

void	finish_process(t_list *exec, t_list *tokens, t_list *envp, char *input)
{
	free_list(exec, free_lst_exec);
	free_list(tokens, free_lst_tokens);
	free_list(envp, free_lst_env);
	free(input);
	close_fds();
	exit(2);
}

void	redirect_and_execute(t_list *exec, t_list *tokens,
	t_list *envp, char *input)
{
	int	pid;
	int	status;

	pid = -2;
	status = 0;
	handle_redirect(exec->node);
	if (validate_command(exec->node))
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			if (execve(exec->node->data->execution->path,
					exec->node->data->execution->command_table,
					exec->node->data->execution->envp) == -1)
				finish_process(exec, tokens, envp, input);
		}
		else
		{
			wait(&status);
			finish_process(exec, tokens, envp, input);
		}
	}
	finish_process(exec, tokens, envp, input);
}
