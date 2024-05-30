/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/29 14:55:26 by codespace        ###   ########.fr       */
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

	exec->node = exec->head;
	if (!exec)
		return (1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		redirect_and_execute(exec->node, tokens, envp, input);
	else
		waitpid(pid, NULL, 0);
	return (0);
}

void	finish_process(t_node *exec, t_list *tokens, t_list *envp, char *input)
{
	t_list	*lst_exec;
	(void)exec;

	lst_exec = init_exec_addr();
	free_list(lst_exec, free_lst_exec);
	free_list(tokens, free_lst_tokens);
	free_list(envp, free_lst_env);
	free(input);
	close_fds();
	exit(2);
}

void	redirect_and_execute(t_node *exec, t_list *tokens,
	t_list *envp, char *input)
{
	int	pid;

	pid = -2;
	handle_redirect(exec);
	if (validate_command(exec, envp))
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			if (execve(exec->data->execution->path,
					exec->data->execution->command_table,
					exec->data->execution->envp) == -1)
				finish_process(exec, tokens, envp, input);
		}
		else
		{
			waitpid(pid, NULL, 0);
			finish_process(exec, tokens, envp, input);
		}
	}
	finish_process(exec, tokens, envp, input);
}
