/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/29 17:20:47 by dlamark-         ###   ########.fr       */
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

	status = 0;
	ft_stdout = dup(1);
	ft_stdin = dup(0);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork : ");
		return (-1);
	}
	if (pid == 0)
	{
		if (handle_redirect(exec->head, envp, ft_stdin, ft_stdout) == -1)
			finish_process(exec, tokens, envp, input);
		execute_and_update_envp(exec, envp);
		finish_process(exec, tokens, envp, input);
	}
	else
		wait_for_children(&status, envp);
	return (0);
}

int	execute_and_update_envp(t_list *exec, t_list *envp)
{
	handle_execution(exec->head, envp);
	if (exec->node->data->exec->command_table
		&& exec->node->data->exec->path == NULL
		&& ft_strncmp("126", ft_get_env("?"), 3) != 0)
	{
		update_env_list(envp, "?", "127");
		ft_putstr_fd("command not found\n", 2);
	}
	return (0);
}
