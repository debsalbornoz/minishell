/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/02 17:13:13 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_simple_command(t_list *exec,
	t_list *tokens, t_list *envp, char *input)
{
	int	pid;
	int	ft_stdout;
	int	ft_stdin;

	ft_stdout = dup(1);
	ft_stdin = dup(0);
	handle_heredoc(exec->head);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		redirect_and_execute(exec->head, envp);
		ft_stdout = dup2(ft_stdout, 1);
		ft_stdin = dup2(ft_stdin, 0);
		if (exec->node->data->exec->path == NULL)
		{
			update_env_list(envp, "?", "127");
			printf("Command not found\n");
		}

		finish_process(exec, tokens, envp, input);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

int	redirect_and_execute(t_node *exec, t_list *envp)
{
	if (handle_redirect(exec, envp) == -1)
		return (-1);
	if (validate_command(exec))
	{
		if (execve(exec->data->exec->path,
				exec->data->exec->command_table,
				exec->data->exec->envp) == -1)
			return (-1);
	}
	return (0);
}
