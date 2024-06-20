/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/20 12:16:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_simple_command(t_list *exec,
	t_list *tokens, t_list *envp, char *input)
{
	int		pid;
	int		ft_stdout;
	int		ft_stdin;
	int		status;
	char	*sts;

	status = 0;
	ft_stdout = dup(1);
	ft_stdin = dup(0);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		redirect_and_execute(exec->head, envp);
		ft_stdout = dup2(ft_stdout, 1);
		ft_stdin = dup2(ft_stdin, 0);
		if (exec->node->data->exec->command_table
			&& exec->node->data->exec->path == NULL)
		{
			update_env_list(envp, "?", "127");
			ft_putstr_fd("Command not found\n", 2);
		}
		finish_process(exec, tokens, envp, input);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			sts = ft_itoa(WEXITSTATUS(status));
			update_env_list(envp, "?", sts);
			free (sts);
		}
	}
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
