/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/01 18:24:26 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if (exec->node->data->exec->path == NULL)
		{
			update_env_list(envp, "?", "127");
			printf("Command not found\n");
		}
		redirect_and_execute(exec->head);
		ft_stdout = dup2(ft_stdout, 1);
		ft_stdin = dup2(ft_stdin, 0);
		finish_process(exec, tokens, envp, input);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

int	redirect_and_execute(t_node *exec)
{
	handle_redirect(exec);
	if (validate_command(exec))
	{
		if (execve(exec->data->exec->path,
				exec->data->exec->command_table,
				exec->data->exec->envp) == -1)
			return (-1);
	}
	return (0);
}
