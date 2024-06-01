/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/01 16:45:57 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/wait.h>

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
	int	pid;
	int	ft_stdout;
	int	ft_stdin;

	handle_heredoc(exec->head);
	ft_stdout = dup(1);
	ft_stdin = dup(0);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		redirect_and_execute(exec->node, envp);
		ft_stdout = dup2(ft_stdout, 1);
		ft_stdin = dup2(ft_stdin, 0);
		finish_process(exec, tokens, envp, input);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

int	redirect_and_execute(t_node *exec, t_list *envp)
{
	handle_redirect(exec);
	if (validate_command(exec, envp))
	{
		if (execve(exec->data->exec->path,
				exec->data->exec->command_table,
				exec->data->exec->envp) == -1)
			return (-1);
	}
	return (0);
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
